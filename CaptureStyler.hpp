#include "TwilightEngineCore/TwilightEngine.hpp"

#include <list>

class CaptureStyler : public RenderObject2D
{
	private:
	Point<float> position;
	std::list<Point<float>> line_points;
	int frames_until_next_point;
	bool is_active;
	public:
	CaptureStyler():
	position(0, 0)
	{
		frames_until_next_point = 10;
		setLayer(DrawLayer::UI);
		is_active = false;
	}

	void update() override
	{
		if(!is_active)
		{
			if(line_points.size() != 0)
			{
				line_points.clear();
			}
			return;
		}
		position.setX(GetMousePosition().x);
		position.setY(GetMousePosition().y);
		if(frames_until_next_point == 0)
		{
			line_points.push_front(position);
			frames_until_next_point = 1;
			if(30 < line_points.size())
			{
				line_points.pop_back();
			}
		}
		frames_until_next_point--;
	}
	void handleInputs() override
	{
		is_active = (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyDown(KEY_SPACE));
	}

	void draw() override
	{
		if(is_active)
		{
			DrawCircle(position.getX(), position.getY(), 10, WHITE);
		}
		if(line_points.size() < 3)
		{
			return;
		}
		std::vector<Vector2> bezier_points;

		Point<float> average_point(0, 0);
		for(auto point : line_points)
		{
			average_point += point;
			bezier_points.push_back((Vector2){point.getX(), point.getY()});
		}
		average_point = average_point / line_points.size();

		float lowest_distance = 10000.f;
		for(auto point : line_points)
		{
			float current_distance = average_point.distanceTo(point);
			if(current_distance < lowest_distance)
			{
				lowest_distance = current_distance - 10;
			}
		}
		DrawCircle(average_point.getX(), average_point.getY(), lowest_distance, RED);
		DrawCircle(average_point.getX(), average_point.getY(), 5, GREEN);

		DrawSplineBasis(bezier_points.data(), bezier_points.size(), 1, BLUE);
		// for(int i = 0; i != line_points.size() - 1; i++)
		// {
		// 	auto it1 = std::next(line_points.begin(), i);
		// 	auto it2 = std::next(line_points.begin(), i + 1);
		// 	Line2D(
		// 		*it1,
		// 		*it2,
		// 		BLUE
		// 	).draw();
		// }
	}

	std::string getType() override
	{
		return "CaptureStyler";
	}
};