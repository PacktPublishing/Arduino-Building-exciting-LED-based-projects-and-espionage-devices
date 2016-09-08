#include <avr/pgmspace.h>
// Useful for Sound Analysis
#include <ffft.h>
#include <math.h>
// Required for communication with I2C device
#include <Wire.h>
#include <Adafruit_GFX.h>
// Required for Adafruit LED backpack
#include <Adafruit_LEDBackpack.h>

// Microphone connects to Analog Pin 0. ADC Pin 0 for Arduino Uno
#define ADC_INPUT 0

int16_t audio_capture[FFT_N];
complex_t fft_buffer[FFT_N];
uint16_t output_spectrum[FFT_N / 2];
volatile byte buffer_position = 0;

byte peakValue[8], dotCount = 0, colCount = 0;
int col[8][10], minAvgLevel[8], maxAvgLevel[8], colDiv[8];

static const uint8_t PROGMEM
// Noise to be removed from each column. Adjust the values as per the requirements
noiseToDeduct[64] = { 8, 6, 6, 5, 3, 4, 4, 4, 3, 4, 4, 3, 2, 3, 3, 4,
                      2, 1, 2, 1, 3, 2, 3, 2, 1, 2, 3, 1, 2, 3, 4, 4,
                      3, 2, 2, 2, 2, 2, 2, 1, 3, 2, 2, 2, 2, 2, 2, 2,
                      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4
                    },
                    // Equalizer to remove the noise and neutralize the noise at the bass end.
equalizer[64] = {
  255, 175, 218, 225, 220, 198, 147, 99, 68, 47, 33, 22, 14,  8,  4,  2,
  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
},

// We want to fit the output of FFT spectrum to 8 columns.
// All the bins from the output specrtum is not useful.
// we will following bins for the column output.
// Below table contains details about number of bins to take and index from where it will start
// along with the nin numbers.
column0[] = {  2,  1,
               111,   8
            },
            column1[] = {  4,  1,
                           19, 186,  38,   2
                        },
                        column2[] = {  5,  2,
                                       11, 156, 118,  16,   1
                                    },
                                    column3[] = {  8,  3,
                                                   5,  55, 165, 164,  71,  18,   4,   1
                                                },
                                        column4[] = { 11,  5,
                                                      3,  24,  89, 169, 178, 118,  54,  20,   6,   2,   1
                                                    },
                                            column5[] = { 17,  7,
                                                          2,   9,  29,  70, 125, 172, 185, 162, 118, 74,
                                                          41,  21,  10,   5,   2,   1,   1
                                                        },
                                                column6[] = { 25, 11,
                                                              1,   4,  11,  25,  49,  83, 121, 156, 180, 185,
                                                              174, 149, 118,  87,  60,  40,  25,  16,  10,   6,
                                                              4,   2,   1,   1,   1
                                                            },
                                                    column7[] = { 37, 16,
                                                                  1,   2,   5,  10,  18,  30,  46,  67,  92, 118,
                                                                  143, 164, 179, 185, 184, 174, 158, 139, 118,  97,
                                                                  77,  60,  45,  34,  25,  18,  13,   9,   7,   5,
                                                                  3,   2,   2,   1,   1,   1,   1
                                                                },
                                                        // This contains list of all the data bin for all 8 columns
* const binsToUse[]  = {
  column0, column1, column2, column3,
  column4, column5, column6, column7
};

Adafruit_BicolorMatrix LEDmatrix = Adafruit_BicolorMatrix();

void setup() {
  uint8_t i, j, nBins, binNum, *outputData;

  memset(peakValue, 0, sizeof(peakValue));
  memset(col , 0, sizeof(col));

  for (i = 0; i < 8; i++) {
    minAvgLevel[i] = 0;
    maxAvgLevel[i] = 512;
    outputData = (uint8_t *)pgm_read_word(&binsToUse[i]);
    nBins = pgm_read_byte(&outputData[0]) + 2;
    binNum = pgm_read_byte(&outputData[1]);
    for (colDiv[i] = 0, j = 2; j < nBins; j++)
      colDiv[i] += pgm_read_byte(&outputData[j]);
  }

  LEDmatrix.begin(0x70);

  // Init ADC free-run mode; f = ( 16MHz/prescaler ) / 13 cycles/conversion
  ADMUX  = ADC_INPUT; // Channel sel, right-adj, use AREF pin
  ADCSRA = _BV(ADEN)  | // ADC enable
           _BV(ADSC)  | // ADC start
           _BV(ADATE) | // Auto trigger
           _BV(ADIE)  | // Interrupt enable
           _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // 128:1 / 13 = 9615 Hz
  ADCSRB = 0;
  DIDR0  = 1 << ADC_INPUT;
  TIMSK0 = 0;

  sei(); // Enable interrupts
}

void loop() {
  uint8_t  i, x, L, *outputData, nBins, binNum, weighting, c;
  uint16_t minLvl, maxLvl;
  int      level, y, sum;

  while (ADCSRA & _BV(ADIE)); // Wait for audio sampling to finish

  fft_input(audio_capture, fft_buffer);   // Samples -> complex #s
  buffer_position = 0;                   // Reset sample counter
  ADCSRA |= _BV(ADIE);             // Resume sampling interrupt
  fft_execute(fft_buffer);          // Process complex data
  fft_output(fft_buffer, output_spectrum); // Complex -> spectrum

  // Remove noise and apply equalizers
  for (x = 0; x < FFT_N / 2; x++) {
    L = pgm_read_byte(&noiseToDeduct[x]);
    output_spectrum[x] = (output_spectrum[x] <= L) ? 0 :
                         (((output_spectrum[x] - L) * (256L - pgm_read_byte(&equalizer[x]))) >> 8);
  }

  // Fill background w/colors, then idle parts of columns will erase
  LEDmatrix.fillRect(0, 0, 8, 3, LED_RED);    // Upper section
  LEDmatrix.fillRect(0, 3, 8, 2, LED_YELLOW); // Mid
  LEDmatrix.fillRect(0, 5, 8, 3, LED_GREEN);  // Lower section

  // Downsample spectrum output to 8 columns:
  for (x = 0; x < 8; x++) {
    outputData   = (uint8_t *)pgm_read_word(&binsToUse[x]);
    nBins  = pgm_read_byte(&outputData[0]) + 2;
    binNum = pgm_read_byte(&outputData[1]);
    for (sum = 0, i = 2; i < nBins; i++)
      sum += output_spectrum[binNum++] * pgm_read_byte(&outputData[i]); // Weighted
    col[x][colCount] = sum / colDiv[x];                    // Average
    minLvl = maxLvl = col[x][0];
    for (i = 1; i < 10; i++) { // Get range of prior 10 frames
      if (col[x][i] < minLvl)
      {
        minLvl = col[x][i];
      }
      else if (col[x][i] > maxLvl)
      {
        maxLvl = col[x][i];
      }
    }
    // minLvl and maxLvl indicate the extents of the FFT output, used
    // for dynamically setting the min and max level of the column.

    if ((maxLvl - minLvl) < 8)
    {
      maxLvl = minLvl + 8;
    }
    minAvgLevel[x] = (minAvgLevel[x] * 7 + minLvl) >> 3; // Dampen min/max levels
    maxAvgLevel[x] = (maxAvgLevel[x] * 7 + maxLvl) >> 3; // (fake rolling average)

    // Second fixed-point scale based on dynamic min/max levels:
    level = 10L * (col[x][colCount] - minAvgLevel[x]) /
            (long)(maxAvgLevel[x] - minAvgLevel[x]);

    // Clip output and convert to byte:
    if (level < 0L)
    {
      c = 0;
    }
    else if (level > 10)
    {
      c = 10; // Allow dot to go a couple pixels off top
    }
    else
    {
      c = (uint8_t)level;
    }

    if (c > peakValue[x])
    {
      peakValue[x] = c; // Keep dot on top
    }

    if (peakValue[x] <= 0) // No output
    {
      LEDmatrix.drawLine(x, 0, x, 7, LED_OFF);
      continue;
    }
    else if (c < 8) // Partial column?
    {
      LEDmatrix.drawLine(x, 0, x, 7 - c, LED_OFF);
    }

    // The 'peak' dot color varies, but doesn't necessarily match
    // the three screen regions...yellow has a little extra influence.
    y = 8 - peakValue[x];
    if (y < 2)
    {
      LEDmatrix.drawPixel(x, y, LED_RED);
    }
    else if (y < 6)
    {
      LEDmatrix.drawPixel(x, y, LED_YELLOW);
    }
    else
    {
      LEDmatrix.drawPixel(x, y, LED_GREEN);
    }
  }

  LEDmatrix.writeDisplay();

  // Every third frame, make the peak pixels drop by 1:
  if (++dotCount >= 3)
  {
    dotCount = 0;
    for (x = 0; x < 8; x++)
    {
      if (peakValue[x] > 0) peakValue[x]--;
    }
  }

  if (++colCount >= 10)
  {
    colCount = 0;
  }
}

ISR(ADC_vect) { // Audio-sampling interrupt
  static const int16_t noiseThreshold = 4;
  int16_t sample = ADC; // values between 0-1023

  audio_capture[buffer_position] =
    ((sample > (512 - noiseThreshold)) &&
     (sample < (512 + noiseThreshold))) ? 0 :
    sample - 512; // Sign-convert for FFT; -512 to +511

  if (++buffer_position >= FFT_N) ADCSRA &= ~_BV(ADIE); // Turn off the interrupt once buffer is full
}

