#include "../5V.hpp"


void OutputPort::draw(NVGcontext *vg) {
	Port::draw(vg);
	if (gRackWidget->activeWire && gRackWidget->activeWire->outputPort) {
		Port::drawGlow(vg);
	}
}

void OutputPort::onDragStart() {
	if (connectedWire) {
		// Disconnect wire from this port, but set it as the active wire
		connectedWire->outputPort = NULL;
		connectedWire->updateWire();
		gRackWidget->activeWire = connectedWire;
		connectedWire = NULL;
	}
	else {
		connectedWire = new WireWidget();
		connectedWire->outputPort = this;
		gRackWidget->wireContainer->addChild(connectedWire);
		gRackWidget->activeWire = connectedWire;
	}
}

void OutputPort::onDragDrop(Widget *origin) {
	if (connectedWire) return;
	if (gRackWidget->activeWire) {
		if (gRackWidget->activeWire->outputPort) return;
		gRackWidget->activeWire->outputPort = this;
		connectedWire = gRackWidget->activeWire;
	}
}
