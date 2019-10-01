#set title "Árvore de Steiner"
set style arrow 1 nohead lw 4
#Seta tamanho da janela automaticamente de acordo com os dados
set autoscale
set nokey

numPontos=4

set key off
splot 'gnuplot/edges.tsv' using 1:2:3:($4-$1):($6-$3) with lines lc rgb "green" lw 2 notitle, \
'gnuplot/xyz.tsv' using 1:2:3 with points lc rgb "red" pointsize 3 pointtype 7,\
'gnuplot/xyz.tsv' using 1:2:3:($0+numPontos+1) with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle,\
'gnuplot/xyzFixos.tsv' using 1:2:3 with points lc rgb "black" pointsize 3 pointtype 7,\
'gnuplot/xyzFixos.tsv' using 1:2:3:($0+1) with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle,\


pause -1
