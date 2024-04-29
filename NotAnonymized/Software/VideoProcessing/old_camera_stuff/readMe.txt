usage: process_one_video.py [-h] [-v VIDEO] [-o OUTPUT] [-a MIN_AREA] [-d]
ValueError: time data '2019-04-15 10 37 12-A' does not match format '%Y-%m-%d %H %M %S-P'
I changed A to P in the video file's name



Ok. This code tries to track objects moving through the frame. So, id==0, is the first object we picked up in the video. Notice that id==1 gets written first because I save them to the file once they are complete (basically when they leave the frame).

Does "seconds" represent the length of the detected motion? (Yes)

Does "frames" indicate the number of frames where the motion was detected? (Yes, it's another measure of the length of that individual track.)

What are these variables: 
start_time_offset_seconds (when did the track start — seconds from the start of the clip)
end_time_offset_seconds (when did the track stop — seconds from the start of the clip)
up_moves (how much movement [in pixels] did the track's center move upward in the frame)
down_moves (same as above, only downward)
left_moves (same... only left)
right_moves (same... only right)
up [up_moves / max(up_moves + down_moves + left_moves + right_moves, 1) — it's basically an attempt to quantify how much of the total movement is in the upward direction]
down, left, right (same as up, only down, left, and right), 
percent_right, percent_left (in what percentage of the frames did the object move to the right — or left)
left_to_right (how many times did the object's center cross the midline from left to right?)
right_to_left (how many times did the object's center cross the midline from right to left?)
Note, these are trying to provide numerical ways to reason about the motion. For example, a simple left to right movement through the doorway would have a high percent_right value, a low percent_left value, and a left_to_right value of 1. Its right_to_left value would be 0. 

Also, when you see super short tracks (like id==13), this often means that the script identified a part of an existing track (a hand, foot, or object someone is holding) briefly as a second object. 

It's not a particularly sophisticated script, and it definitely gets confused sometimes. So, I had the script produce annotated videos of the tracks so it would be easy to watch the weird cases and handle them manually. You should watch them, as it will help you better understand what the script is actually doing.

Also, if you ever have a significant lighting change in the frame (someone turns on or off lights), it could throw things off considerably for the rest of the segment (probably producing a lot of false-positive tracks). Since our segments are short (1 minute, right?), I figured we could probably handle these cases manually rather than spending a lot of time developing a better tracker.

On the upside, it doesn't seem to miss movement through the frame (it might if someone walked around dressed as a tile floor 😀). So, in the worst case, we just have to go through and manually classify the different tracks, which should still be a LOT simpler than what we had to do last time (basically watch all of the video at high speed to find events).