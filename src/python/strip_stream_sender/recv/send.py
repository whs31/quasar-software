from strip import sender
import time
remote = '127.0.0.1:48455'
size = 1024

strip_sender = sender.Sender(remote, size)

i = 0
while True:
    try:
        f = open("pack/{}".format(i), 'rb')
    except:
        break
    data = f.read(size)
    strip_sender.put(data)
    i+=1
    if len(data) < size:
        time.sleep(0.1)

strip_sender.stop()
