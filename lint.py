import glob
import subprocess

for filename in glob.iglob('**/*.c', recursive=True):
	subprocess.run(["uncrustify", "-c", "C:/Users/George/Documents/ElectronicsProjects/Uncrustify/u_cnf.cfg", "--no-backup", filename])

for filename in glob.iglob('**/*.h', recursive=True):
	subprocess.run(["uncrustify", "-c", "C:/Users/George/Documents/ElectronicsProjects/Uncrustify/u_cnf.cfg", "--no-backup", filename])

print("All done, mate.")