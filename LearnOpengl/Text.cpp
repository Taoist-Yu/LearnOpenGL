#include "Text.h"
#include<glad/glad.h>
#include<sstream>

void Text::Draw(std::wstring str, float x, float y, glm::vec3 color)
{
	Text text(str, x, y, color);
	text.show();
}

void Text::Draw(std::string str, float x, float y, glm::vec3 color)
{
	Text text(str, x, y, color);
	text.show();
}

Text::Text(std::wstring str, float x, float y, glm::vec3 color)
{
	setText(str);
	this->x = x;
	this->y = y;
	this->color = color;
}

Text::Text(std::string str, float x, float y, glm::vec3 color)
{
	setText(str);
	this->x = x;
	this->y = y;
	this->color = color;
}

Text::~Text()
{
}

void Text::setText(std::wstring str)
{
	this->str.clear();
	std::wstringstream ss;
	ss << str;
	ss >> this->str;
}

void Text::setText(std::string str)
{
	this->str.clear();
	for (char c : str)
	{
		this->str.push_back(c);
	}
}

void Text::setColor(float r, float g, float b, float a)
{
	this->color = glm::vec4(r, g, b, a);
}

void Text::show()
{
	GLuint list = glGenLists(1);
	glColor3f(color.r, color.g, color.b);
	glRasterPos2f(x, y);
	for (TCHAR c : str)
	{
		wglUseFontBitmaps(wglGetCurrentDC(), c, 1, list);
		glCallList(list);
	}
	glDeleteLists(list, 1);
}
