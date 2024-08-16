// Smart-Homie_Monitoring.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "libs/Crow/include/crow.h"
#include "libs/Crow/include/crow/middlewares/cors.h"

int main()
{
	crow::App<crow::CORSHandler> app;
	auto& cors = app.get_middleware<crow::CORSHandler>();

	cors
		.global()
		.headers("X-Custom-Header", "Upgrade-Insecure-Requests")
		.methods("POST"_method, "GET"_method)
		.prefix("/cors")
		.origin("example.com")
		.prefix("/nocors")
		.ignore();

	CROW_ROUTE(app, "/monitor/").methods("GET"_method)([](const crow::request& req) {
		std::cout << "Received request: " << req.url << std::endl;
		if (req.method == "GET"_method) {
			return crow::response("Hello from monitor. I monitor devices connected from Smart Homie!");
		}
		});
	app.port(8081).multithreaded().run();
}
