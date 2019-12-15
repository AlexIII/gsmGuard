#! /usr/bin/env python
# -*- coding: utf-8 -*-

import ttk
import tkFileDialog
from Local import Local
from resource_path import resource_path

class EventTable(object):
    def __init__(self, root):
        self.tree = tree = ttk.Treeview(root, columns = ('event', 'val'))
        tree.heading('#0', text = Local('Date'))
        tree.heading('#1', text = Local('Event'))
        tree.heading('#2', text = Local('Value'))
        tree.pack(side = 'left', padx = (3,0), pady = 3)
        
        vsb = ttk.Scrollbar(root, orient="vertical", command=tree.yview)
        vsb.pack(side = 'right', fill = 'y', padx = (0,3), pady = 3)
        tree.configure(yscrollcommand=vsb.set)
        
    def add(self, entry):
        self.tree.insert('', 'end', text=entry[0], values=entry[1:])
        
class EventHistory:
    def __init__(self, root, CSVdata):
        root.resizable(False, False)
        root.title('GSMguard event history')
        root.iconbitmap(resource_path('./gg-icon.ico'))
        ttk.Button(root, text = Local('Save as') + " *.csv", command = lambda: self.save()).pack(side = 'top', anchor = 'w', padx = 3, pady = 3)
        et = EventTable(root)
        self.csv = CSVdata
        data = CSVdata.strip().split('\n')[1:]
        for row in data:
            et.add(row.strip().split(';'))
        
    def save(self):
        f = tkFileDialog.asksaveasfile(mode='w', defaultextension=".csv")
        if f is None:
            return
        f.write(self.csv)
        f.close()
        
data = """date;event;value
11.06.18 12:33;Light change;36%
11.06.18 16:18;Movement detected
11.06.18 19:20;Door open
12.06.18 11:32;Low temperature;-20*C
13.06.18 12:44;High temperature;36*C
11.06.18 12:33;Light change;36%
11.06.18 16:18;Movement detected
11.06.18 19:20;Door open
12.06.18 11:32;Low temperature;-20*C
13.06.18 12:44;High temperature;36*C
11.06.18 12:33;Light change;36%
11.06.18 16:18;Movement detected
11.06.18 19:20;Door open
12.06.18 11:32;Low temperature;-20*C
13.06.18 12:44;High temperature;36*C
11.06.18 12:33;Light change;36%
11.06.18 16:18;Movement detected
11.06.18 19:20;Door open
12.06.18 11:32;Low temperature;-20*C
13.06.18 12:44;High temperature;36*C
"""

if __name__ == "__main__":
    import Tkinter
    root = Tkinter.Tk()
    EventHistory(root, data)
    root.mainloop()