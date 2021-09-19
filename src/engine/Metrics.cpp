#include "Metrics.h"

#include <iostream>

Metric::Metric(double limit)
{
	deltaSum = 0;
	Metric::limit = limit;

	currentFps = 0;
	fps = 0;

	currentUpdates = 0;
	updates = 0;
}

void Metric::Update(double delta)
{
	deltaSum += delta;
	currentUpdates++;
}

void Metric::Render()
{
	currentFps++;
}

void Metric::Print()
{
	if (deltaSum > limit) {
		updates = currentUpdates / limit;
		fps = currentFps / limit;

		currentUpdates = 0;
		currentFps = 0;
		deltaSum = 0;

		std::cout << "Updates: " << updates << " FPS: " << fps << std::endl;
	}
}
