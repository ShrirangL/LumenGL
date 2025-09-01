import os
import argparse

def dump_cpp_and_h_files_to_txt(root_folder, output_file):
    with open(output_file, 'w', encoding='utf-8') as outfile:
        for subdir, _, files in os.walk(root_folder):
            for file in files:
                if file.endswith(('.cpp', '.h')):
                    file_path = os.path.join(subdir, file)
                    try:
                        with open(file_path, 'r', encoding='utf-8', errors='ignore') as infile:
                            outfile.write(f"\n\n// ===== File: {file_path} =====\n")
                            outfile.write(infile.read())
                    except Exception as e:
                        print(f"Failed to read {file_path}: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Dump contents of .cpp and .h files into a .txt file.")
    parser.add_argument("-o", "--output", default="output_dump.txt", help="Output text file (default: output_dump.txt)")

    args = parser.parse_args()
    
    current_dir = os.getcwd()
    dump_cpp_and_h_files_to_txt(current_dir, args.output)
    print(f"All .cpp and .h files from '{current_dir}' dumped into '{args.output}'")
