import matplotlib.pyplot as plt

logs = ""
with open('logs') as f:
    logs = f.read()

logs = logs.strip().split('\n')

graph_proc = {}

min_ticks = 100000

for line in logs:
    tick, pid, queue = map(int, line.split(' '))
    pid = str(pid)

    if tick < min_ticks:
        min_ticks = tick

    if pid not in graph_proc.keys():
        graph_proc[pid] = {"x": [tick], "y": [queue]}
    else:
        graph_proc[pid]['x'].append(tick)
        graph_proc[pid]['y'].append(queue)

for pid in graph_proc.keys():
    for i in range(len(graph_proc[pid]['x'])):
        graph_proc[pid]['x'][i] -= min_ticks


for pid in graph_proc.keys():
    plt.plot(graph_proc[pid]['x'], graph_proc[pid]['y'], label=pid)

plt.legend()
plt.show()
