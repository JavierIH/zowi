# PlatformIO pre-script: build the Arduino sketch folder given by `custom_sketch`
# instead of src/, so the sketches keep the Arduino IDE layout (folder/folder.ino).
Import("env")

sketch = env.GetProjectOption("custom_sketch")
env.Replace(PROJECT_SRC_DIR=env.subst("$PROJECT_DIR/" + sketch))
