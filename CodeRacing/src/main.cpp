#include "types/types.h"

#include "offline-client-server/server.h"
#include "offline-client-server/client.h"

#include <thread>
#include <iostream>

struct Map
{
	CoordsVertex firstLine;
	CoordsVertex secondLine;
};

class SharedMemory
{
private:
	Car car;
	Map map;

public:
	SharedMemory() {}
	~SharedMemory() {}

	const Map& getMap()
	{
		return map;
	}

	/*const CoordsVertex& getCarPoz()
	{
		return *car.poz;
	}

	const std::vector<Radar>& getCarRadars()
	{
		return *car.radars;
	}

	void setCarPoz(const Coords& offset)
	{
		for (auto& coord : car.poz)
		{
			coord.x += offset.x;
			coord.y += offset.y;
		}
	}*/
};

/*
Coords finish = {Map::firstLine.back(), Map::secondLine.back()};

std::vector<std::pair<float, float>> poz;
poz[0].first;
poz[0].second;

std::vector<Coords> poz;
poz[0].x;
poz[0].y;
*/

int main()
{
	std::thread serverThread([]() {
		try
		{
			Server server("127.0.0.1", 5555);
			server.start();
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}
		});


	std::thread clientThread([]() {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		try
		{
			Client client("127.0.0.1", 5555);
			client.start();
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}
		});

	serverThread.join();
	clientThread.join();



	return 0;
}