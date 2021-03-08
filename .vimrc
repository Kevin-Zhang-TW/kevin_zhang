" Specify a directory for plugins
" - For Neovim: stdpath('data') . '/plugged'
" - Avoid using standard Vim directory names like 'plugin'
call plug#begin('~/.vim/plugged')

" Make sure you use single quotes

" Shorthand notation; fetches https://github.com/junegunn/vim-easy-align
Plug 'rakr/vim-one'
Plug 'joshdick/onedark.vim'
" Plug 'sheerun/vim-polyglot'

" Initialize plugin system
call plug#end()


set ar fdm=manual nu ts=4 sw=4 cindent rnu
sy on
command Fast r /home/kevin/Documents/Code/templates/fastio.cpp
command Usaco r /home/kevin/usaco
set makeprg=g++\ -DKEV\ -std=c++20\ -fsanitize=undefined\ %\ -o\ ~/run
noremap<F4> ggVGddd"+P
noremap<C-n> :!ran<CR><CR>
noremap<F12> :!clear && testit<CR>
noremap<F5> ggVGd:0 r /home/kevin/Documents/Code/template.cpp<CR>:1,16fold<CR>
noremap<F9> :!~/run<CR>
noremap<F7> :w  <CR>:!g++ -DKEV -std=c++20 -fsanitize=undefined "%" -o ~/run<CR>

"noremap<silent> <C-F8> :!wl-paste > /home/kevin/Documents/Code/inputf.txt <CR>
noremap<silent> <C-F8> :!xclip -selection clipboard -o > /home/kevin/Documents/Code/inputf.txt <CR>
map<F8> <ESC><C-F8>:!clear && printf "            input : \n" && cat /home/kevin/Documents/Code/inputf.txt && printf "\n\n            output : \n" && ~/run</home/kevin/Documents/Code/inputf.txt<CR>
map<F10> <F7><F8>
nmap <leader>y :%y+<CR>
autocmd BufNewFile *.cpp -r ~/Documents/Code/template.cpp
autocmd BufNewFile *.sh -r ~/basic_script.sh !chmod+x\ %
autocmd Filetype python map<F7> :w<CR>:!python %<CR>
noremap<C-p> I//<ESC>
inoremap<C-p> <ESC>I// <ESC>
noremap<C-t> :tabnew test.cpp<CR>

if (has("termguicolors"))
set termguicolors
endif


" colo onedark

" autocmd ColorScheme * call onedark#extend_highlight("Function", { "gui": "bold" })
" let g:hybrid_transparent_background = 1
set background=dark
let g:enable_bold_font = 1
colorscheme hybrid_material
hi comment guifg=#81a2be
hi LineNr guifg=#f0c674


au Bufenter *.tex map<F7> :w<CR>:!xelatex "%:r".tex<CR> | map<F8> :!okular "%:r".pdf & exit<CR> 
" For Arduino Usage
 au BufRead,BufNewFile *.ino,*.pde map<F7> :w<CR>:!clear<CR>:!arduino-cli compile -b arduino:avr:nano:cpu=atmega328old "%:p:h"   --build-properties build.extra_flags=-std=c++14 <CR>
 au BufRead,BufNewFile *.ino,*.pde map<F8> :!arduino-cli upload -p /dev/ttyUSB0 -b arduino:avr:nano:cpu=atmega328old '%:p:h'<CR>
" 
" au BufRead,BufNewFile *.ino,*.pde map<F7> :w<CR>:!clear<CR>:!arduino-cli compile -b arduino:avr:mega "%:p:h"   --build-properties build.extra_flags=-std=c++14 <CR>
" au BufRead,BufNewFile *.ino,*.pde map<F8> :!arduino-cli upload -p /dev/ttyACM0 -b arduino:avr:mega '%:p:h'<CR>
au BufRead,BufNewFile *.ino,*.pde map<F9> :!minicom -D /dev/ttyUSB0 -b 38400 <CR>
"For Neovim > 0.1.5 and Vim > patch 7.4.1799 < https://github.com/vim/vim/commit/61be73bb0f965a895bfb064ea3e55476ac175162 >
"Based on Vim patch 7.4.1770 (`guicolors` option) < https://github.com/vim/vim/commit/8a633e3427b47286869aa4b96f2bfc1fe65b25cd >
" < https://github.com/neovim/neovim/wiki/Following-HEAD#20160511 >



