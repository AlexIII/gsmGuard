#! /usr/bin/env python
# -*- coding: utf-8 -*-

# for windows xp
# import sys  
# reload(sys)  
# sys.setdefaultencoding('cp1251')

import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import ttk
import tkFileDialog
from Local import Local
from resource_path import resource_path

class makePlot:
    def __init__(self, root, xlabels, temps, plotLabels):
        colors = ['red', 'blue', 'gray']
        fig = Figure(figsize=(7,3))
        sp = fig.add_subplot(111)
        N = len(temps[0])
        for i in range(len(temps)):
            sp.plot(range(N), temps[i], color=colors[i], label=plotLabels[i])
        if N <= 10:
            sp.set_xticks(range(N))
            sp.set_xticklabels(xlabels, rotation=90)
        else:
            sp.set_xticks([i*2 for i in range(N/2)])
            sp.set_xticks(range(N), minor=True)
            sp.set_xticklabels([xlabels[i*2] for i in range(N/2)], rotation=90)
        sp.grid(True)
        sp.set_ylabel("*C", fontsize=14)
        sp.legend()
        fig.set_tight_layout(True)

        canvas = FigureCanvasTkAgg(fig, master=root)
        canvas.get_tk_widget().pack(padx = 5, pady = 5)
        canvas.draw()

class TempPlot:
    def __init__(self, root, CSVdata):
        root.resizable(False, False)
        root.title('GSMguard temperature')
        root.iconbitmap(resource_path('./gg-icon.ico'))
        ttk.Button(root, text = Local('Save as') + " *.csv", command = lambda: self.save()).pack(side = 'top', anchor = 'w', padx = 3, pady = 3)
        self.csv = CSVdata
        data = CSVdata.strip().split('\n')
        fields = data[0].strip().split(';')
        data = data[1:]
        smp = [[] for i in fields]
        for i in range(len(data)):
            es = data[i].strip().split(';')
            for j in range(len(es)):
                smp[j].append(es[j])
        temp = [[float(j) for j in i] for i in smp[1:]]
        makePlot(root, smp[0], temp, fields[1:])  
        
    def save(self):
        f = tkFileDialog.asksaveasfile(mode='w', defaultextension=".csv")
        if f is None:
            return
        f.write(self.csv)
        f.close()        

data = """date;max;min;avg
01.02.17;19.484364;16.23697;18.0230367
02.02.17;20.779836;17.31653;19.2213483
03.02.17;20.665128;17.22094;17.22094
04.02.17;21.223572;17.68631;17.68631
05.02.17;21.283692;17.73641;19.6874151
06.02.17;23.1855;19.32125;21.4465875
07.02.17;23.181072;19.31756;23.181072
08.02.17;25.442964;21.20247;25.442964
09.02.17;26.897328;22.41444;24.8800284
10.02.17;26.540616;22.11718;24.5500698
"""

if __name__ == "__main__":
    import Tkinter
    root = Tkinter.Tk()
    TempPlot(root, data)
    root.mainloop()