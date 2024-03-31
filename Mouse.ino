#include "HID-Project.h"
#include <hidboot.h>
#include <usbhub.h>

USB     Usb;
USBHub     Hub(&Usb);
HIDBoot < USB_HID_PROTOCOL_KEYBOARD | USB_HID_PROTOCOL_MOUSE > HidComposite(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

int delta[2];
// Mouse
int lmb = 0;
int rmb = 0;
int mmb = 0;
class MouseRptParser : public MouseReportParser
{
  protected:
    void OnMouseMove(MOUSEINFO *mi);
    void OnLeftButtonUp(MOUSEINFO *mi);
    void OnLeftButtonDown(MOUSEINFO *mi);
    void OnRightButtonUp(MOUSEINFO *mi);
    void OnRightButtonDown(MOUSEINFO *mi);
    void OnMiddleButtonUp(MOUSEINFO *mi);
    void OnMiddleButtonDown(MOUSEINFO *mi);
};

void MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{
  delta[0] = mi->dX;
  delta[1] = mi->dY;
};
void MouseRptParser::OnLeftButtonUp  (MOUSEINFO *mi)
{
  lmb = 0;
};
void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi)
{
  lmb = 1;
};
void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi)
{
  rmb = 0;
};
void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi)
{
  rmb = 1;
};
void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi)
{
  mmb = 0;
};
void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi)
{
  mmb = 1;
};

MouseRptParser MousePrs;

void setup()
{
  AbsoluteMouse.begin();
  Mouse.begin();
  Serial.begin( 115200 );
  Usb.Init();
  HidComposite.SetReportParser(1, &MousePrs);
  HidMouse.SetReportParser(0, &MousePrs);
}

void loop()
{
  delta[0] = 0;
  delta[1] = 0;
  Usb.Task();
   // Left Mouse
  if (lmb == 0){
    Mouse.release(MOUSE_LEFT);
  } else if (lmb == 1){
    Mouse.press(MOUSE_LEFT);
  }
  // Right Mouse
  if (rmb == 0){
    Mouse.release(MOUSE_RIGHT);
  } else if (rmb == 1){
    Mouse.press(MOUSE_RIGHT);
  }
  // Middle Mouse
  if (mmb == 0){
    Mouse.release(MOUSE_MIDDLE);
  } else if (mmb == 1){
    Mouse.press(MOUSE_MIDDLE);
  }


  if (Serial.available() > 0)
  {
    // Read Data
    String data = Serial.readStringUntil('x');

    // Gets demarcation between deltaX and DeltaY
    int ohHiMarc = data.indexOf(':');
    Serial.println(data);

    // DeltaX & DeltaY
    delta[0] = data.substring(0, ohHiMarc).toInt();
    delta[1] = data.substring(ohHiMarc + 1).toInt();
    //AbsoluteMouse.moveTo(delta[0], delta[1]);
    AbsoluteMouse.moveTo(delta[0], delta[1]);
  } else{
    Mouse.move(delta[0], delta[1]);
  }
}
