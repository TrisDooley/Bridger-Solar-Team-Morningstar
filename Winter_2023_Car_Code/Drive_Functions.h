int calculate_digi_pot(int accel) {
  //converts the acceleration potentionmeter value (between 475 and 875) to a 0-255 range for SPI, and flips it because of the potentiometer mounting
  if(accel < 50) {
    accel = ACCEL_ZERO_POSITION;
  }
  int calculated_digipot = 0;
  calculated_digipot = int(map(accel, ACCEL_MAX_POSITION, ACCEL_ZERO_POSITION, 255, 0));

  //truncate the value to between 0 and 255
  calculated_digipot = max(calculated_digipot, 0);
  calculated_digipot = min(calculated_digipot, 255);

  return calculated_digipot;
}

//ISR that iturrupts on falling edge of every pulse from motor controller, records timer value to caculate speed
unsigned long SpeedPeriodPrev; //This rolls over every 49.7 days 
unsigned long SpeedPeriodCur;

float SpeedPeriodDiff = 0;
int CurSpeedVal = 0;

void SpeedRead(){
  SpeedPeriodPrev = SpeedPeriodCur;
  SpeedPeriodCur = millis();
}

void calculate_speed(){
  SpeedPeriodDiff = abs(SpeedPeriodCur-SpeedPeriodPrev);
  CurSpeedVal = 1/((SpeedPeriodDiff*PulseNum)/1000) * WheelCirc * 0.0568;
  if(CurSpeedVal < 1) CurSpeedVal = 0;
  if(CurSpeedVal > 99) CurSpeedVal = 99;
}