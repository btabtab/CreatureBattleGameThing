#pragma once

#include "TwilightEngineCore/TwilightEngine.hpp"
#include "TwilightEngineCore/Point.hpp"

class PuzzleButton : public RenderObject2D
{
protected:
	int frames_until_fail, frames_left;
	Point<float> centre;
	bool was_press_succesfull;
	
public:
	PuzzleButton(Point<float> position, int starting_frame_count):
	centre(position)
	{
		frames_until_fail = frames_left = starting_frame_count;
	}
	float getProgress()
	{
		return (float)((float)frames_left / (float)frames_until_fail);
	}
	void update() override
	{
		deletionCheck();
	}
	void deletionCheck()
	{
		frames_left--;
		if(frames_left < 0 || was_press_succesfull)
		{
			deleteMe();
		}
	}
};

class TimedButton : public PuzzleButton
{
private:
	float max_radius;
public:
	TimedButton(int starting_frame_count, int start_radius, Point<float> position = Point<float>(GetScreenWidth() / 2, GetScreenHeight() / 2)):
	PuzzleButton(position, starting_frame_count)
	{
		max_radius = start_radius;
		was_press_succesfull = false;
	}
	void draw() override
	{
		DrawCircle(
					centre.getX(),
					centre.getY(),
					max_radius * 0.1,
					WHITE
					);
		DrawCircleLines(
					centre.getX(),
					centre.getY(),
					max_radius * getProgress(),
					WHITE
					);
	}
	std::string getType() override
	{
		return "TimedButton";
	}
	void handleInputs() override
	{
	}
	void update() override
	{
		PuzzleButton::update();
	}
};

class PathwayButton : public PuzzleButton
{
private:
	Point<float> a, b;
	Point<float> current_point;
	
public:

	PathwayButton(Point<float> a, Point<float> b, int starting_frame_count = 60):
	PuzzleButton(Point<float>(0, 0), starting_frame_count),
	a(a),
	b(b),
	current_point(a + (b - a))
	{
		Point<float> swap = a;
		if(b.getX() < a.getX())
		{
			a = b;
			b = swap;
		}
		was_press_succesfull = false;
	}

	void update() override
	{
		// frames_left--;
		centre = a + ((b - a) * getProgress());
		deletionCheck();
	}

	void draw() override
	{
		Point<float>	c(a.getX(), a.getY()),
						d(b.getX(), b.getY());

		// Line2D(c, d, RED).draw();
		DrawCircle(centre.getX(), centre.getY(), 2.f, WHITE);
		DrawCircleLines(
					centre.getX(),
					centre.getY(),
					60 * getProgress(),
					WHITE
					);
		// Line2D(centre, a, BLUE).draw();
		// Line2D(centre, b, GREEN).draw();
	}

	std::string getType() override
	{
		return "PathwayButton";
	}
};