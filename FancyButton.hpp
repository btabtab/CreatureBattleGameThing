#pragma once

#include "TwilightEngineCore/TwilightEngine.hpp"
#include "TwilightEngineCore/Point.hpp"
#include "PuzzleButtonScoreTracker.hpp"

class PuzzleButton : public RenderObject2D
{
protected:
	int frames_until_fail, frames_left;
	Point<float> centre;
	bool was_press_succesful;
	PuzzleButtonScoreTracker* tracker;
	float max_radius;
	
public:
	PuzzleButton(Point<float> position, int starting_frame_count, PuzzleButtonScoreTracker* tracker = nullptr):
	centre(position),
	tracker(tracker)
	{
		frames_until_fail = frames_left = starting_frame_count;
	}
	float getProgress()
	{
		return (float)((float)frames_left / (float)frames_until_fail);
	}
	void update() override
	{
		if(was_press_succesful)
		{
			if(tracker != nullptr)
			{
				std::cout << "added " << 1 - getProgress() << "\n";
				tracker->addToScore(1 - getProgress());
			}
		}
		deletionCheck();
	}
	void deletionCheck()
	{
		frames_left--;
		if(frames_left < 0 || wasPressSuccesful())
		{
			deleteMe();
		}
	}

	bool wasPressSuccesful()
	{
		return was_press_succesful;
	}
	void handleInputs() override
	{
		if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return;
		}
		Point<float> click_position(GetMousePosition().x, GetMousePosition().y);

		Point<float> bound(
								max_radius * getProgress(),
								max_radius * getProgress()
								);
		
		if(
			click_position.getX() < (centre + bound).getX()
			&&
			(centre - bound).getX() < click_position.getX()
			&&
			(centre - bound).getY() < click_position.getY()
			&&
			click_position.getY() < (centre + bound).getY()
			)
		{
			was_press_succesful = true;
		}
	}
	void drawBounds()
	{

		Point<float> bound(
								max_radius * getProgress(),
								max_radius * getProgress()
								);
		
		DrawCircle((centre - bound).getX(), (centre - bound).getY(), 5, BLUE);

		DrawCircle((centre + bound).getX(), (centre + bound).getY(), 5, RED);
	}
};

class TimedButton : public PuzzleButton
{
private:
public:
	TimedButton(int starting_frame_count, int start_radius, Point<float> position = Point<float>(GetScreenWidth() / 2, GetScreenHeight() / 2), PuzzleButtonScoreTracker* tracker = nullptr):
	PuzzleButton(position, starting_frame_count, tracker)
	{
		max_radius = start_radius;
		was_press_succesful = false;
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
		drawBounds();
	}
	std::string getType() override
	{
		return "TimedButton";
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

	PathwayButton(Point<float> a, Point<float> b, int starting_frame_count = 60, PuzzleButtonScoreTracker* tracker = nullptr):
	PuzzleButton(Point<float>(0, 0), starting_frame_count, tracker),
	a(a),
	b(b),
	current_point(a + (b - a))
	{
		max_radius = 60;
		Point<float> swap = a;
		if(b.getX() < a.getX())
		{
			a = b;
			b = swap;
		}
		was_press_succesful = false;
	}

	void update() override
	{
		// frames_left--;
		centre = a + ((b - a) * getProgress());
		deletionCheck();
	}

	void draw() override
	{
		drawBounds();
		Point<float>	c(a.getX(), a.getY()),
						d(b.getX(), b.getY());

		// Line2D(c, d, RED).draw();
		DrawCircle(centre.getX(), centre.getY(), 2.f, WHITE);
		DrawCircleLines(
					centre.getX(),
					centre.getY(),
					max_radius * getProgress(),
					WHITE
					);
		Line2D(centre, a, WHITE).draw();
		// Line2D(centre, b, GREEN).draw();
	}

	std::string getType() override
	{
		return "PathwayButton";
	}
};