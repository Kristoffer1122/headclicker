import requests
import base64
import os

owner = "Kristoffer1122"
repo = "headclicker"
ref = "39e648e781686937bde4dd194234d5e8216c6098"

files_to_get = [
    "src/headclicker.c",
    "src/enemys.c", 
    "src/enemys.h",
    "src/weapon_Firing.c",
    "src/weapon_Firing.h",
    "src/sound_effect.c",
    "src/sound_effects.h",
    "Makefile",
    "README.md"
]

for file_path in files_to_get:
    url = f"https://api.github.com/repos/{owner}/{repo}/contents/{file_path}?ref={ref}"
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json()
        if 'content' in data:
            content = base64.b64decode(data['content']).decode('utf-8')
            os.makedirs(os.path.dirname(file_path), exist_ok=True)
            with open(file_path, 'w') as f:
                f.write(content)
            print(f"Downloaded: {file_path}")
        else:
            print(f"No content in: {file_path}")
    else:
        print(f"Failed to get {file_path}: {response.status_code}")
