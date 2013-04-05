vcap
====

video capture base for dshow, the solution file exist in packages/capture/capture.sln.

baseclasses: Microsoft Directshow baseclasses.
ffmfilter: An directshow filter with ffmpeg as audio/video encoder.
vcapture: The capture library with wrappers the complexity of directshow and ffmpeg. It'll capture input from camera/microphone, and export rtmp data. You can replace rtmp with anything you like, for example rtp or tcp/udp. There need be a red5 server for rtmp exporting.

Be careful when you need to change ffmfilter, the pts/dts need to be correctly handled.
