#set title "Árvore de Steiner"
set style arrow 1 nohead lw 4
#Seta tamanho da janela automaticamente de acordo com os dados
set autoscale
set nokey

numPontos=4

plot "gnuplot/edges.dat" using 1:2:($3-$1):($6-$4) with vectors arrowstyle 1,\
#"gnuplot/ptfixos.dat" u 1:2:(0.1) with circles fill solid lc rgb "black" notitle,\
#"gnuplot/ptfixos.dat" using 1:2:($0+1) with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle,\
#"gnuplot/ptsteiner.dat" u 1:2:(0.1) with circles fill solid lc rgb "red" notitle,\
#"gnuplot/ptsteiner.dat" using 1:2:($0+numPontos+1) with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle,

pause -1
