// TileMap.h : Header for the windows application.
// Generative System: Perlin Noise
// Used in Games: FPS, RPG, Platformers, MOBA
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <noise/noise.h>

class TileMap : public sf::Drawable, public sf::Transformable
{
	public:
		bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			//Apply the transform
			states.transform *= getTransform();

			//Apply the tileset texture
			states.texture = &m_tileset;

			//Draw the vertex array
			target.draw(m_vertices, states);
		}

		sf::VertexArray m_vertices;
		sf::Texture m_tileset;
};

