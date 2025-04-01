import sys

def replace_in_file(input_file, output_file, placeholder, replacement):
    with open(input_file, 'r') as infile:
        content = infile.read()
    content = content.replace(placeholder, replacement)
    with open(output_file, 'w') as outfile:
        outfile.write(content)

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Usage: replace_in_file.py <input_file> <output_file> <placeholder> <replacement>")
        sys.exit(1)
    replace_in_file(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])