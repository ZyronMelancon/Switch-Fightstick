typedef enum {
  SWITCH_Y       = 0x01,
  SWITCH_B       = 0x02,
  SWITCH_A       = 0x04,
  SWITCH_X       = 0x08,
  SWITCH_L       = 0x10,
  SWITCH_R       = 0x20,
  SWITCH_ZL      = 0x40,
  SWITCH_ZR      = 0x80,
  SWITCH_MINUS   = 0x100,
  SWITCH_PLUS    = 0x200,
  SWITCH_LCLICK  = 0x400,
  SWITCH_RCLICK  = 0x800,
  SWITCH_HOME    = 0x1000,
  SWITCH_CAPTURE = 0x2000,
} joyButtons_t;

#define STICK_MIN      0
#define STICK_CENTER 128
#define STICK_MAX    255

typedef struct {
  uint16_t Button; // 16 buttons; see JoystickButtons_t for bit mapping
  uint8_t  HAT;    // HAT switch; one nibble w/ unused nibble
  uint8_t  LX;     // Left  Stick X
  uint8_t  LY;     // Left  Stick Y
  uint8_t  RX;     // Right Stick X
  uint8_t  RY;     // Right Stick Y
  uint8_t  VendorSpec;
} joyReport_t;

joyReport_t joyReport;

void setup(void);
void loop(void);
void setButton(joyReport_t *joy, uint16_t button);
void clearButton(joyReport_t *joy, uint16_t button);
void sendJoyReport(joyReport_t *report);

void setup() 
{
  for(int i = 2; i < 5; i++)
    pinMode(i, INPUT_PULLUP);

  Serial.begin(115200);
  delay(200);
}

// Send an HID report to the USB interface
void sendJoyReport(joyReport_t *report)
{
    Serial.write((uint8_t *)report, sizeof(joyReport_t));
}

void setButton(joyReport_t *joy, uint16_t button)
{
    joy->Button |= button;
}

void clearButton(joyReport_t *joy, uint16_t button)
{
    joy->Button &= ~button;
}

void loop() 
{
  setButton(&joyReport, SWITCH_Y);
  sendJoyReport(&joyReport);
  delay(200);
  clearButton(&joyReport, SWITCH_Y);
  sendJoyReport(&joyReport);
  delay(200);
}
