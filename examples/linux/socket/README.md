# wind2rrd

Want to generate a cool wind speed and direction graph like this one?
The wind direction is scaled back 10x so 30 means 300 degrees:

![Example graph](README.png?raw=true "Example")

To do this, you'll need to build and run *candump_reader*
to read the candump output, then format it into a rrdtool
update statement.

First, create your data files. If you only want wind, you
can delete the last two:

```
for arg in 1:2900 15:1400 60:1465 240:4380
do
avg="$avg RRA:AVERAGE:0.5:$arg"
min="$min RRA:MIN:0.5:$arg"
max="$max RRA:MAX:0.5:$arg"
done
rrdcreate -s 1 wind.rrd DS:speed:GAUGE:60:0:100 DS:dir:GAUGE:60:0:360 $avg $min $max
rrdcreate -s 1 depth.rrd DS:depth:GAUGE:60:0:U $avg $min $max
rrdcreate -s 1 heading.rrd DS:heading:GAUGE:60:0:360 $avg $min $max
```
Check that everything is working:
```
wind2rrd - | head
```
You should see a few update statements.

You'll then need to run this for a while:

```
wind2rrd
```

There's a wind2rrd.service file you can copy over to 

You can then generate some amazing graphs, like the one above,
using this command:

```
/usr/bin/rrdtool graph - \
--imgformat=PNG \
--pango-markup  \
--slope-mode \
--base=1000 \
--height=150 \
--width=500 \
--alt-autoscale-max \
--lower-limit='0' \
--color BACK#F3F3F3 \
--color CANVAS#FDFDFD \
--color SHADEA#CBCBCB \
--color SHADEB#999999 \
--color FONT#000000 \
--color AXIS#2C4D43 \
--color ARROW#2C4D43 \
--color FRAME#2C4D43 \
--border 1 --font TITLE:11:'Arial' \
--font AXIS:8:'Arial' \
--font LEGEND:8:'Courier' \
--font UNIT:8:'Arial' \
--font WATERMARK:6:'Arial' \
--slope-mode \
DEF:a='/var/lib/cacti/rra/foo.rrd':'speed':MAX \
DEF:b='/var/lib/cacti/rra/foo.rrd':'dir':MAX \
CDEF:cdefe='b,10,/' \
LINE1:a#0000FFFF:  \
GPRINT:a:LAST:'Cur\:%8.2lf %s'  \
GPRINT:a:AVERAGE:'Avg\:%8.2lf %s'  \
GPRINT:a:MAX:'Max\:%8.2lf %s\n'  \
LINE1:cdefe#C04000FF:  \
GPRINT:b:LAST:'Cur\:%8.2lf %s'  \
GPRINT:b:AVERAGE:'Avg\:%8.2lf %s'  \
GPRINT:b:MAX:'Max\:%8.2lf %s\n' > README.png
```

You can also interface this into something like cacti, which
will let you interactively explore the graph.
