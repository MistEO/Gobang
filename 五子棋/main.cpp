#include <cstdlib>
#include <Windows.h>

#include "Table.h"
#include "AI.h"

constexpr int Debug = true;

void win(const int who);

int main(void)
{
	Table t;
	AI ai(t);
	t.display();
	while (true)
	{
		char x; int y;
		std::cout << "Your choice: ";
		std::cin >> x >> y;
		if (Debug && x == 'Z') {
			t.undo();
			system("CLS");
			t.display();
			continue;
		}
		while (!t.check_point(Point(x, y))) {
			std::cout << "Please try again: ";
			std::cin >> x >> y;
		}
		t.play(Point(x, y), White);
		system("CLS");
		t.display();

		if (t.check_win()) {
			win(White);
			return 0;
		}

		Point ai_point = ai.calc();
		t.play(ai_point, Black);

		system("CLS");
		t.display();
		std::cout << "AI: " << ai_point << std::endl;
		if (t.check_win()) {
			win(Black);
			return 0;
		}

	}
	return 0;
}

void win(const int who)
{
	if (who == White) {
		std::cout << "You Win!" << std::endl;
	}
	else if (who == Black) {
		std::cout << "AI Win!" << std::endl;
	}
	Sleep(6000);
}
