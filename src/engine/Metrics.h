#pragma once
#ifndef MATRICS_CLASS_H
#define MATRICS_CLASS_H

class Metric {
public:
	double deltaSum;
	double limit;

	double currentFps;
	double fps;

	double currentUpdates;
	double updates;

	Metric(double limit);

	void Update(double delta);
	void Render();

	void Print();
};

#endif // !MATRICS_CLASS_H
