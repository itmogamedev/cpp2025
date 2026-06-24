#include "resource.h"
#include "utilities.h"

// all resources
std::unordered_map<std::string,
  std::unique_ptr<Resources::Base>> Resources::Base::members;

// font parser
Resources::Font::Font(std::string path)
{
  // load the file
  std::vector<uchar> data = Utilities::ReadFile(path);

  // split by newlines
  std::vector<std::string> lines;
  lines.push_back("");
  for (char c : data)
    if (c == '\n')
      lines.push_back("");
    else if (c != ' ' && c != '\r')
      lines.back() += c;

  // get width and height
  width = std::stoi(lines[0]);
  height = std::stoi(lines[1]);
  spacingx = std::stoi(lines[2]);
  spacingy = std::stoi(lines[3]);

  // get characters
  for (int i = 4; i < lines.size(); i++)
    chars[lines[i][0]] = lines[i].substr(1);
}

// text loader
Resources::Text::Text(std::string path)
{  
  // read file
  bytes = Utilities::ReadFile(path);

  // split by newlines
  lines.push_back("");
  
  // get lines
  for (char c : bytes)
    if (c == '\n')
      lines.push_back("");
    else if (c != '\r')
      lines.back() += c;
}

// palettes parser
Resources::Palettes::Palettes(std::string path)
{
  // read file
  auto data = Utilities::ReadFile(path);

  // first element
  list.push_back(std::vector<uint>());

  // going through each line
  for (int c = 0; c < data.size(); c++)
  {
    // some insane hex parsing
    while (c < data.size() && data[c] != '\n') {
      if (data[c] == '#') {
        uint color = 0;
        for (int i = 0; i < 6; i++)
          color = (color << 4)
            | (data[++c] < 'a'
              ? data[c] - '0'
              : data[c] - 'a' + 10);
        list.back().push_back(color);
      }
      else
        c++;
    }

    // if it's a new line
    if (c < data.size())
      list.push_back(std::vector<uint>());
  }
}