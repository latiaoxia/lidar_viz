let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/project/lidar/test_code/src
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +6 main.cpp
badd +1 term://.//31703:/bin/bash
badd +1 ~/project/lidar/test_code/CMakeLists.txt
badd +12 CMakeLists.txt
badd +26 shader.hpp
badd +1 term://.//31679:/bin/bash
badd +38 shader.cpp
badd +1 ~/project/lidar/test_code/.gitignore
badd +9 vshader.vsh
badd +9 fshader.fsh
argglobal
silent! argdel *
$argadd main.cpp
set splitbelow splitright
wincmd t
set winminheight=1 winminwidth=1 winheight=1 winwidth=1
argglobal
if bufexists('term://.//31679:/bin/bash') | buffer term://.//31679:/bin/bash | else | edit term://.//31679:/bin/bash | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 1 - ((0 * winheight(0) + 32) / 65)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 054|
tabedit fshader.fsh
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd t
set winminheight=1 winminwidth=1 winheight=1 winwidth=1
exe '1resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 1resize ' . ((&columns * 135 + 135) / 271)
exe '2resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 2resize ' . ((&columns * 135 + 135) / 271)
exe 'vert 3resize ' . ((&columns * 135 + 135) / 271)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 02|
wincmd w
argglobal
if bufexists('main.cpp') | buffer main.cpp | else | edit main.cpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 53 - ((26 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
53
normal! 0
wincmd w
argglobal
if bufexists('term://.//31703:/bin/bash') | buffer term://.//31703:/bin/bash | else | edit term://.//31703:/bin/bash | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 158 - ((64 * winheight(0) + 32) / 65)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
158
normal! 056|
wincmd w
exe '1resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 1resize ' . ((&columns * 135 + 135) / 271)
exe '2resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 2resize ' . ((&columns * 135 + 135) / 271)
exe 'vert 3resize ' . ((&columns * 135 + 135) / 271)
tabnext 2
if exists('s:wipebuf') && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 winminheight=1 winminwidth=1 shortmess=filnxtToOFc
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
