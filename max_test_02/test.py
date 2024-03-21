from openai import OpenAI
import openai


# Function to read the content of your text file
def read_text_file(file_path):
    with open(file_path, "r", encoding="utf-8") as file:
        return file.read()


def analyze_text(text):
    client = OpenAI()
    openai.api_key = "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"
    response = client.chat.completions.create(
        model="gpt-3.5-turbo",  # Adjust the model version as needed
        messages=[
        {"role": "user", "content": "hey"},
        ],
    )
    return response.choices[0].text.strip()


# Main script
if __name__ == "__main__":
    # Replace 'path_to_your_file.txt' with the path to the text file you want to analyze
    text_to_analyze = read_text_file("save.txt")

    # Get the analysis from the ChatGPT API
    analysis = analyze_text(text_to_analyze)
    print("Analysis:", analysis)
