let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/project/lidar/test_code/src
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +18 main.cpp
badd +1 ~/project/lidar/test_code/CMakeLists.txt
badd +12 CMakeLists.txt
badd +12 shader.hpp
badd +1 term://.//36379:/bin/bash
badd +1 shader.cpp
badd +1 ~/project/lidar/test_code/.gitignore
badd +11 vshader.vsh
badd +4 fshader.fsh
badd +1 term://.//36404:/bin/bash
badd +32 term://.//36421:/bin/bash
badd +52 camera.hpp
badd +53 camera.cpp
argglobal
silent! argdel *
$argadd main.cpp
set splitbelow splitright
wincmd t
set winminheight=1 winminwidth=1 winheight=1 winwidth=1
argglobal
if bufexists('term://.//36379:/bin/bash') | buffer term://.//36379:/bin/bash | else | edit term://.//36379:/bin/bash | endif
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
normal! 0
tabedit main.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd t
set winminheight=1 winminwidth=1 winheight=1 winwidth=1
exe '1resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 1resize ' . ((&columns * 135 + 135) / 271)
exe '2resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 2resize ' . ((&columns * 135 + 135) / 271)
exe '3resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 3resize ' . ((&columns * 135 + 135) / 271)
exe '4resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 4resize ' . ((&columns * 135 + 135) / 271)
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
let s:l = 53 - ((18 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
53
normal! 0
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
let s:l = 130 - ((30 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
130
normal! 05|
wincmd w
argglobal
if bufexists('term://.//36404:/bin/bash') | buffer term://.//36404:/bin/bash | else | edit term://.//36404:/bin/bash | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 351 - ((31 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
351
normal! 056|
wincmd w
argglobal
if bufexists('camera.hpp') | buffer camera.hpp | else | edit camera.hpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 33 - ((18 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
33
normal! 05|
wincmd w
exe '1resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 1resize ' . ((&columns * 135 + 135) / 271)
exe '2resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 2resize ' . ((&columns * 135 + 135) / 271)
exe '3resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 3resize ' . ((&columns * 135 + 135) / 271)
exe '4resize ' . ((&lines * 32 + 34) / 68)
exe 'vert 4resize ' . ((&columns * 135 + 135) / 271)
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
