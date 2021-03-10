#ARQUIVO COM AS CONFIGURAÇÕES DA ARVORE GNU

#set title "Árvore de Steiner"
set style arrow 1 nohead lw 4
#Seta tamanho da janela automaticamente de acordo com os dados
set autoscale
unset key

numPontos=4

set key off
splot 'gnuplot/ptEdges-2021-03-10 11h23m36s.tsv' using 1:2:3 with lines lc rgb "black" lw 1 notitle, \
'gnuplot/ptSteiner-2021-03-10 11h23m36s.tsv' using 1:2:3 with points lc rgb "red" pointsize 3 pointtype 7,\
'gnuplot/ptSteiner-2021-03-10 11h23m36s.tsv' using 1:2:3:($0+numPontos+1) with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle,\
'gnuplot/ptFixos-2021-03-10 11h23m36s.tsv' using 1:2:3 with points lc rgb "black" pointsize 3 pointtype 7,\
'gnuplot/ptFixos-2021-03-10 11h23m36s.tsv' using 1:2:3:($0+1) with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle,\

pause -1
