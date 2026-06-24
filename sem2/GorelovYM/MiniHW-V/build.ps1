# make sure that you have sfml installed
$files = (Get-ChildItem -Recurse -Filter "*.cpp" | ForEach-Object { $_.FullName })
g++ --std=c++17 $files -o main.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -w -mwindows
if ($?) { Start-Process ./main.exe }
(Write-Host (Get-ChildItem -Recurse -Include *.h, *.cpp -File | Get-Content | Measure-Object -Line).Lines) > lines.txt