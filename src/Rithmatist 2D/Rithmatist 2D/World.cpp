#include "World.h"

World::World()
{

}

std::vector<sf::Vector2f> World::extractPoints(sf::Packet& packet)
{
	std::vector<sf::Vector2f> points;

	sf::Uint16 pointCount;
	packet >> pointCount;

	for (int i = 0; i < pointCount; i++)
	{
		float x, y;
		packet >> x >> y;

		points.push_back(sf::Vector2f(x, y));
	}

	return points;
}

void World::gameLoop()
{

	//Initialize Networking
	std::cout << "Listener? (y/n)" << std::endl;

	bool listen;
	char checkListener;

	std::cin >> checkListener;

	checkListener == 'y' ? listen = true : listen = false;

	unsigned short port;

	std::cout << "Input Port: " << std::endl;
	std::cin >> port;

	sf::TcpSocket socket;

	if (listen)
	{
		sf::TcpListener listener;

		if (listener.listen(port) != sf::Socket::Done)
		{
			std::cout << "Fail listen" << std::endl;
		}

		if (listener.accept(socket) != sf::Socket::Done)
		{
			std::cout << "Fail accept" << std::endl;
		}
		else
		{
			std::cout << "Success" << std::endl;
		}
	}
	else
	{
		std::cout << "Input Connection IP" << std::endl;
		std::string inputIP;
		std::cin >> inputIP;
		sf::IpAddress ip(inputIP);

		sf::Socket::Status status = socket.connect(ip, port);
		if (status != sf::Socket::Done)
		{
			std::cout << "Fail connect" << std::endl;
		}
		else
		{
			std::cout << "Success" << std::endl;
		}
	}
	
	socket.setBlocking(false);

	//Packets
	sf::Packet sender;
	sf::Packet reciever;

	sf::Uint16 locCount = 0;
	sf::Uint16 recieveCount;

	//Setup
	Render rendering;
	InputHandler handler;

	std::vector<GameActor*> activeActors_;
	
	Panel *drawModePanel_ = new Panel("Textures/Frame.png", sf::Vector2f(64.0f, 64.0f), sf::Vector2f(0.0f, 0.0f));
	activeActors_.push_back(drawModePanel_);

	Panel *divider_ = new Panel();
	divider_->background.setSize(sf::Vector2f(1000.0f, 4.0f));
	divider_->background.setPosition(sf::Vector2f(0.0f, 498.0f));
	divider_->background.setFillColor(sf::Color(209, 161, 0));
	activeActors_.push_back(divider_);
	

	std::vector<Vigor*> activeVigors_;

	sf::RenderWindow *window = &rendering.window;
	bool m_keepM = false;

	double previous = gameClock.getElapsedTime().asMilliseconds();
	double lag = 0.0;
	while (rendering.window.isOpen())
	{
		double current = gameClock.getElapsedTime().asMilliseconds();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		handler.input(rendering, window);

		//Fixed Time Loop
		while (lag >= MS_PER_UPDATE)
		{
			//Keep mouse cursor in window
			/*if (m_keepM)
			{
				int maxX = window->getSize().x;
				int maxY = window->getSize().y;

				int mX = sf::Mouse::getPosition(*window).x;
				int mY = sf::Mouse::getPosition(*window).y;

				if (mX < 0 || mY < 0 || mX > maxX || mY > maxY)
				{
					if (mX < 0)
						mX = 0;
					else if (mX > maxX)
						mX = maxX;

					if (mY < -30)
						mY = -30;
					else if (mY > maxY)
						mY = maxY;

					sf::Mouse::setPosition(sf::Vector2i(mX, mY), *window);
				}
			}*/

			drawModePanel_->update(handler);
			handler.handleDraw(activeActors_, activeVigors_, window);

			//Delete dead actors
			for (int i = 0; i < activeVigors_.size(); i++)
			{
				if (activeVigors_[i]->strength <= 0.0001f)
				{
					activeVigors_.erase(activeVigors_.begin() + i);
				}
			}
			for (int i = 0; i < activeActors_.size(); i++)
			{
				if (activeActors_[i]->strength <= 0.0001f)
				{
					delete activeActors_[i];
					activeActors_.erase(activeActors_.begin() + i);
				}
			}

			//Update Vigors
			for (int i = 0; i < activeVigors_.size(); i++)
			{
				activeVigors_[i]->Visualize();
				if (activeVigors_[i]->regPoints.getVertexCount() != 0)
				{
					size_t lineBack = activeVigors_[i]->regPoints.getVertexCount() - 1;
					float x0 = activeVigors_[i]->regPoints[0].position.x;
					float y0 = activeVigors_[i]->regPoints[0].position.y;
					float x1 = activeVigors_[i]->regPoints[lineBack].position.x;
					float y1 = activeVigors_[i]->regPoints[lineBack].position.y;
					for (int j = 0; j < activeActors_.size(); j++)
					{
						if (activeActors_[j]->checkIntersect(x0, y0, x1, y1))
						{
							//std::cout << "Intersection!" << std::endl;
							activeActors_[j]->strength -= activeVigors_[i]->power;
							activeVigors_[i]->strength = 0.0f;
							activeVigors_.erase(activeVigors_.begin() + i);
							break;
						}
					}
				}
			}

			//Update network / opponent
			int a;
			// Send new actors
			for (int i = 0; i < activeActors_.size(); i++)
			{
				if (activeActors_[i]->send)
				{
					a = i;
					activeActors_[i]->send = false; // Dont send again
					activeActors_[i]->pack(sender); // Put point data into sender packet
					
					for (int i = 0; i < 10; i++) // Try up to 10 times
					{
						if (socket.send(sender) == sf::Socket::Partial)  // If partial send, retry
						{
							std::cout << "Partial packet sent\n";
							continue;
						}
						else
						{
							std::cout << "Sent packet\n";
							break;
						}
						
					}
					sender.clear();
				}
			}

			// Receive up to 5 objects
			for (int i = 0; i < 5; i++)
			{
				//IF data to recieve
				if (socket.receive(reciever) != sf::Socket::NotReady)
				{
					int recievedType;
					if (reciever >> recievedType)
					{
						//std::cout << "Recieved Type" << recievedType << std::endl;
						char cType(recievedType);
						//Create object of specified type with points
						if (cType == 'f')
						{
							std::cout << "Make Forbiddance\n";
							activeActors_.push_back(new Forbiddance(extractPoints(reciever)));
						}
						else if (cType == 'w')
						{
							std::cout << "Make Warding\n";
							activeActors_.push_back(new Warding(extractPoints(reciever)));
						}
						else if (cType == 'v')
						{
							std::cout << "Make Vigor\n";
							activeVigors_.push_back(new Vigor(extractPoints(reciever)));
							activeActors_.push_back(activeVigors_.back());
						}
					}
					else 
					{
						std::cout << "Nah\n";
					}
					reciever.clear();
				}
				else // No more to recieve
				{
					break;
				}
			}

			sender.clear();
			reciever.clear();

			//For gameloop DO NOT TOUCH
			lag -= MS_PER_UPDATE;
		}

		//Render
		rendering.renderCycle(lag / MS_PER_UPDATE, activeActors_);
	}

	/*for (int i = 0; i < activeActors_.size(); i++)
	{
		if (activeActors_[i])
		{
			delete activeActors_[i];
		}
	}*/

	//Free vector memory
	std::vector<Vigor*>().swap(activeVigors_);
	std::vector<GameActor*>().swap(activeActors_);
}

