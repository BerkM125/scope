# scope
Simple computer vision CLI for color isolation using contour detection.

## Usage
Since the computer vision aspect of it uses OpenCV, you will need to have the library and its dependencies installed before you can build the source code yourself.
Other than that, most if not all of the functionality can be accessed via the -h or --help arguments in the CLI:

| Argument  | Description |
| ------------- | ------------- |
| -t [integer], --time <integer> | Time limit, image processing will end after this much time passes (milliseconds)  |
| -o <string>,  --output <string> | Path to centroid coordinate data dump if looking to record tracking data  |
| -v <string>, --videosource <string> | Video stream or recording destination path (by default, the source is a default webcamera)  |
| -n <integer>, --contourcount <integer>  | Maximum number of contours to track/identify at the same time |
| -c <string>, --color <string>  | Isolated color choice from Orange, Yellow, Green, Blue, Violet, and Red  |
| -a <integer>, --area <integer>  | Minimum contour area threshold for color identification or tracking  |
| -d, --display  | Choose whether or not to display a window with video and image processing footage (-d to hide)  |
| -m, --morphomode  | Choose whether or not to apply morphological opening/closing (-m to prevent)  |
