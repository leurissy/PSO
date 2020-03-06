#set title "Árvore de Steiner"
set style arrow 1 nohead lw 4
#Seta tamanho da janela automaticamente de acordo com os dados
set autoscale
set nokey

numPontos=20

plot "gnuplot/edges.tsv" using 1:2:($3-$1):($4-$2) with vectors arrowstyle 1,\
"gnuplot/ptFixos.tsv" u 1:2:(0.2) with circles fill solid lc rgb "black" notitle,\
"gnuplot/ptFixos.tsv" using 1:2:($0+1) with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle,\
"gnuplot/ptSteiner.tsv" u 1:2:(0.2) with circles fill solid lc rgb "red" notitle,\
"gnuplot/ptSteiner.tsv" using 1:2:($0+numPontos+1) with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle,

pause -1