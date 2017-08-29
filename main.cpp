#include <cstddef>
#include <cstdint>
#include "hFramework.h"
#include "hCloudClient.h"

void printfOnConsoleInWebIDE()
{
	for (;;) {
		platform.printf("asd %d\r\n", sys.getRefTime());
		sys.delay(1000);
	}
}

void cfgHandler()
{
	//uncomment if you want to stream video from your project using smartphone
	//platform.ui.video.enableTransmission();
	platform.ui.loadHtml({Resource::WEBIDE, "https://zielmicha.github.io/husarion-pages-test/"});
	auto l1 = platform.ui.label("l1");
	auto lb_bat = platform.ui.label("lb_bat");
	auto l2 = platform.ui.label("l2");
	auto b = platform.ui.button("btn1");
}

void onKeyEvent(KeyEventType type, KeyCode code)
{
	//press "up key" on your keyboard in your device UI
	if (code == KeyCode::Up) {
		if (type == KeyEventType::Pressed) {
			LED3.on();
		} else {
			LED3.off();
		}
	}
}

void onButtonEvent(hId id, ButtonEventType type)
{
	static int cnt = 0;
	if (id == "btn1") {
		UiButton b = platform.ui.button("btn1");
		if (type == ButtonEventType::Pressed) {
			b.setText("pressed %u", cnt++);
		} else {
			b.setText("released %u", cnt++);
		}
		LED1.toggle();
	}
}
void hMain()
{
	platform.begin(&RPi);
	platform.ui.configHandler = cfgHandler;
	platform.ui.onKeyEvent = onKeyEvent;
	platform.ui.onButtonEvent = onButtonEvent;

	sys.taskCreate(printfOnConsoleInWebIDE);
	for (;;) {
		sys.delay(500);
		platform.ui.label("l1").setText("uptime %u", (unsigned int)sys.getRefTime());
		platform.ui.label("lb_bat").setText("%f [V]", sys.getSupplyVoltage());
		LED2.toggle();
	}
}
