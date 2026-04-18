import tkinter as tk
from tkinter import messagebox
import random

# คำศัพท์ 5 ตัวอักษร หมวดผลไม้
WORDS = ["apple", "grape", "mango", "lemon", "peach", "melon", "pears", "berry"]

# สี
COLOR_CORRECT = "#6aaa64"   # เขียว
COLOR_PRESENT = "#c9b458"   # เหลือง
COLOR_ABSENT = "#787c7e"    # เทา
COLOR_DEFAULT = "#d3d6da"   # เทาอ่อน

#จำนวนครั้งที่ให้ทาย ความยาวของคำ
MAX_TRIES = 6
WORD_LENGTH = 5

class WordleGame:
    def __init__(self, root):
        self.root = root
        self.root.title("🟩 Wordle for Beginners")

        # สร้างเมนูเกม
        menu = tk.Menu(root)
        root.config(menu=menu)

        game_menu = tk.Menu(menu, tearoff=0)
        menu.add_cascade(label="เมนูเกม", menu=game_menu)
        game_menu.add_command(label="แสดงคำใบ้", command=self.show_hint)
        game_menu.add_command(label="แสดงจำนวนการทายที่เหลือ", command=self.show_remaining_tries)
        game_menu.add_command(label="แสดงคำตอบ", command=self.show_answer)
        
        #สร้างบ็อคช่องทายคำ
        self.grid_frame = tk.Frame(root)
        self.grid_frame.grid(row=0, column=0, columnspan=5, padx=10, pady=10)

        self.entries = []
        for i in range(MAX_TRIES):
            row = []
            for j in range(WORD_LENGTH):
                entry = tk.Entry(self.grid_frame, width=4, font=("Helvetica", 28), justify="center", bd=2, relief="solid")
                entry.grid(row=i, column=j, padx=5, pady=5)
                entry.config(state="disabled", disabledbackground=COLOR_DEFAULT)
                row.append(entry)
            self.entries.append(row)

        #ช่องใส่คำทาย
        self.input_entry = tk.Entry(root, font=("Helvetica", 16), width=15, justify="center")
        self.input_entry.grid(row=1, column=0, columnspan=2, pady=10)
        self.input_entry.bind("<Return>", self.submit_word)

        # Submit button
        self.submit_button = tk.Button(root, text="Submit", font=("Helvetica", 14), command=self.submit_word)
        self.submit_button.grid(row=1, column=2, padx=5)

        # Restart button
        self.restart_button = tk.Button(root, text="Restart", font=("Helvetica", 14), command=self.reset_game)
        self.restart_button.grid(row=1, column=3, columnspan=2)

        #ช่องใส่คำทายแพ้ชนะ
        self.status_label = tk.Label(root, text="", font=("Helvetica", 14))
        self.status_label.grid(row=2, column=0, columnspan=5)

        self.reset_game()

    def submit_word(self, event=None):
        if self.current_row >= MAX_TRIES:
            return

        guess = self.input_entry.get().lower()

        # Try-Except #1: ตรวจสอบความยาวและความถูกต้องของ input
        try:
            if len(guess) != WORD_LENGTH or not guess.isalpha():
                raise ValueError("กรุณากรอกคำที่มี 5 ตัวอักษรภาษาอังกฤษเท่านั้น")
        except ValueError as e:
            self.status_label.config(text=f"{e}")
            return
        # Try-Except #2: ตรวจสอบคำในคลัง
        try:
            if guess not in WORDS:
                raise ValueError("Word not found in the word list.")
        except ValueError as e:
            self.status_label.config(text=f"Error: {e}")
            return

        for i in range(WORD_LENGTH):
            letter = guess[i]
            entry = self.entries[self.current_row][i]
            entry.config(state="normal")
            entry.delete(0, tk.END)
            entry.insert(0, letter.upper())
            entry.config(state="disabled")

            if letter == self.answer[i]:
                color = COLOR_CORRECT
            elif letter in self.answer:
                color = COLOR_PRESENT
            else:
                color = COLOR_ABSENT

            entry.config(disabledbackground=color, disabledforeground="white")

        if guess == self.answer:
            self.status_label.config(text="ยินดีด้วย! คุณชนะแล้ว!")
            self.end_game()
        else:
            self.current_row += 1
            self.input_entry.delete(0, tk.END)
            if self.current_row == MAX_TRIES:
                self.status_label.config(text=f"แพ้! คำตอบคือ: {self.answer.upper()}")
                self.end_game()

    def end_game(self):
        self.input_entry.config(state="disabled")
        self.submit_button.config(state="disabled")

    def reset_game(self):
        try:
            self.answer = random.choice(WORDS)
        except IndexError:
            #Try-Except #3: ในกรณี word list ว่างเปล่า
            self.answer = "error"
            messagebox.showerror("Error", "ไม่พบคำศัพท์ในระบบ")
            return

        self.current_row = 0
        for row in self.entries:
            for entry in row:
                entry.config(state="normal")
                entry.delete(0, tk.END)
                entry.config(disabledbackground=COLOR_DEFAULT, disabledforeground="black", state="disabled")

        self.status_label.config(text="")
        self.input_entry.config(state="normal")
        self.input_entry.delete(0, tk.END)
        self.submit_button.config(state="normal")
        self.input_entry.focus_set()

    # ฟังก์ชันเมนู
    def show_hint(self):
        hint = f": {self.answer[0].upper()}"
        messagebox.showinfo("คำใบ้", hint)

    def show_remaining_tries(self):
        tries_left = MAX_TRIES - self.current_row
        messagebox.showinfo("จำนวนครั้งที่เหลือ", f"คุณเหลือ {tries_left} ครั้ง")

    def show_answer(self):
        messagebox.showinfo("คำตอบ", f"คำตอบคือ: {self.answer.upper()}")

# เรียกใช้งานเกม
if __name__ == "__main__":
    root = tk.Tk()
    game = WordleGame(root)
    root.mainloop()