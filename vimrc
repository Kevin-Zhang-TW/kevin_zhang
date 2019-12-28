set cindent
set autoread
set foldmethod=indent   
set foldnestmax=10
set nofoldenable
set foldlevel=2
set number
set tabstop=4
set shiftwidth=4
sy on
colo desert
set makeprg=g++\ -D_debug\ -std=c++17\ -fsanitize=undefined\ %\ -o\ run.in\ 
map<F12> <F7>:!~/testit<CR>
map<F7> :w<CR>:!clear && g++ -std=c++17 -D_debug -fsanitize=undefined % -o run.in<CR>
noremap<silent> <C-F8> :!xclip -selection clipboard -o > /home/kevin/Documents/Code/inputf.txt <CR>
map<F9> :!./run.in<CR>
map<F8> <ESC><C-F8>:!clear && ./run.in</home/kevin/Documents/Code/inputf.txt>/home/kevin/Documents/Code/outputf.txt && clear && echo "input : " && cat /home/kevin/Documents/Code/inputf.txt && echo "" && echo "output : " &&  cat /home/kevin/Documents/Code/outputf.txt <CR>
nmap <C-y> ggVG"+y''
map <leader> <C-y>
autocmd BufNewFile *.cpp -r /home/kevin/Documents/Code/template.cpp | /maxn
autocmd BufNewFile *.cpp normal zt
map<C-p> I//<ESC>
map<C-t> :tabnew tmp.cpp<CR>
map<F5> ggVGd:0 r /home/kevin/Documents/Code/template.cpp<CR>
