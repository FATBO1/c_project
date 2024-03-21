from openai import OpenAI

client = OpenAI()
var = "who are you"

# Function to read the content of your text file
def read_text_file(file_path):
    with open(file_path, "r", encoding="utf-8") as file:
        return file.read()


text_to_analyze = read_text_file("save.txt")

# example with a system message
response = client.chat.completions.create(
    model="gpt-3.5-turbo",
    messages=[
        {"role": "user", "content": text_to_analyze},
    ],
    temperature=0,
)

print(response.choices[0].message.content)
