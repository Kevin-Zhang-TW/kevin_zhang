set ai
set autoread
set foldmethod=manual
set foldnestmax=10
set nofoldenable
set foldlevel=2
set number
set tabstop=4
set shiftwidth=4
sy on
"colo desert
fu Clipboard_to_text()
	!xclip -selection clipboard -o > /home/kevin/Documents/Code/inputf.txt
endfunction

fu Run_from_Clipboard()
	silent call Clipboard_to_text()
	!clear && printf "            input : \n" && cat /home/kevin/Documents/Code/inputf.txt && printf "\n\n            output : \n" && ~/run.in</home/kevin/Documents/Code/inputf.txt>/home/kevin/Documents/Code/outputf.txt && cat /home/kevin/Documents/Code/outputf.txt
endfunction

set makeprg=g++\ -fdiagnostics-color\ -DKEV\ -std=c++17\ -fsanitize=undefined\ %\ -o\ ~/run.in\ 
map<silent> <C-n> :!ran<CR><CR>
map<F4> :1,$d<CR>dd"+P
map<F12> :!clear && testit<CR>
map<F9> :!~/run.in<CR>
map<F8> :call Run_from_Clipboard()<CR>
map<F7> :w<CR>:!%<CR>
autocmd BufNewFile *.cpp -r /home/kevin/Documents/Code/template.cpp
autocmd BufNewFile *.sh -r /usr/local/bin/basic_script
autocmd BufEnter *.py noremap<F7> :!python % <CR> 
autocmd BufEnter *.cpp map<C-p> I//<ESC> | set cindent | map<F7> :w<CR>:!clear && g++ -std=c++17 -DKEV -fsanitize=undefined % -o ~/run.in<CR>
autocmd BufEnter,BufNewFile *.ino,*.pde noremap<F7> :w<CR>:!clear && arduino-cli compile -b arduino:avr:nano "%:p:h"<CR>

noremap <leader>y ggVG"+y''
map<C-t> :tabnew tmp.cpp<CR>
map<F5> ggVGd:0 r /home/kevin/Documents/Code/template.cpp<CR>



 let g:hybrid_transparent_background = 1
 let g:enable_bold_font = 1
 "For Neovim > 0.1.5 and Vim > patch 7.4.1799 < https://github.com/vim/vim/commit/61be73bb0f965a895bfb064ea3e55476ac175162 >
 "Based on Vim patch 7.4.1770 (`guicolors` option) < https://github.com/vim/vim/commit/8a633e3427b47286869aa4b96f2bfc1fe65b25cd >
 " < https://github.com/neovim/neovim/wiki/Following-HEAD#20160511 >
 if (has("termguicolors"))
   set termguicolors
 endif
 set background=dark
 colorscheme hybrid_material
" 

"call plug#begin('~/.vim/plugged')
"
"Plug 'jacoborus/tender.vim'
"
"call plug#end()
"
"set termguicolors
"syntax enable
"colorscheme tender
