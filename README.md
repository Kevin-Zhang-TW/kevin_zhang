# Training with USACO problems
## Usage
  1. Download the testit file, it's a scrip which tells you your verdict\
  2. Modify the variable { path, file } to what you want\
  3. path means where your 1.in, 1.out, 2.int, 2.out.... is located\
  4. file means the binary file of you cpp file\
Then\
  1. Compile your *X*.cpp to the *path* you set\
  2. Call testit.sh\
  3. See the verdict\
Since some old usaco testcases are in format of I.1, O.2, I.2, O.2.... 
Execute the { convert file name } script first

Stuff to customize :
  1. $path in testit\
  2. $file in testit\
  3. (optional) $max_run_time in testit\
  4. $path in convert name\
  
### Screen shot 
![TLE](https://github.com/Kevin-Zhang-TW/usaco_practice_log/blob/master/TLE.png)
![WA](https://github.com/Kevin-Zhang-TW/usaco_practice_log/blob/master/WA.png)
![AC](https://github.com/Kevin-Zhang-TW/usaco_practice_log/blob/master/AC.png)
### unsupported feature
  1, Segmentation Fault\
  2. Memory Limit\
  
