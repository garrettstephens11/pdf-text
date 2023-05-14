from flask import Flask, request, render_template
import subprocess
import os

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file:
            filename = 'uploaded_file.pdf'
            file.save(filename)
            process = subprocess.run(['./pdf_reader'], stdout=subprocess.PIPE)
            output = process.stdout.decode()
            os.remove(filename)
            return render_template('display.html', text=output)
    return render_template('upload.html')

if __name__ == '__main__':
    app.run(debug=True)
