import sys

from PySide6.QtCore import QPoint, QSettings, Qt, QTime, QTimer
from PySide6.QtGui import QAction, QFont, QMouseEvent
from PySide6.QtWidgets import QApplication, QLabel, QMenu, QVBoxLayout, QWidget


class Clock(QWidget):
    def __init__(self, parent=None) -> None:
        super().__init__(parent)

        # geometry of Mmin window (x, y, width, height)
        self.setGeometry(1100, 800, 180, 60)

        # hide frame
        self.setWindowFlag(Qt.WindowStaysOnTopHint, True)
        self.setWindowFlag(Qt.FramelessWindowHint, True)
        self.setAttribute(Qt.WA_TranslucentBackground)

        # mouse & menu
        self.pressed = False
        self.oldPos = QPoint(0, 0)
        self.setContextMenuPolicy(Qt.CustomContextMenu)
        self.customContextMenuRequested.connect(self.mouseRightMenu)

        # clock object
        clock = QTimer(self)
        clock.timeout.connect(self.showTime)
        clock.start(1000)  # update the clock per second
        self.show()

        self.settings = QSettings(f"{sys.argv[0]}/../config.ini", QSettings.IniFormat)
        font = QFont()
        font.setFamily(self.settings.value("USER/FONT_FAMILY"))
        font.setPointSize(int(self.settings.value("USER/FONT_SIZE")))

        # load settings
        self.settings = QSettings(f"{sys.argv[0]}/../config.ini", QSettings.IniFormat)

        # # font object
        self.font = QFont()
        self.font.setFamily(self.settings.value("DEFAULT/FONT_FAMILY"))
        self.font_size_step = int(self.settings.value("USER/FONT_SIZE_STEP"))

        # label object
        self.label = QLabel()
        self.label.setAlignment(Qt.AlignCenter)

        # layout
        layout = QVBoxLayout(self, spacing=0)
        layout.addWidget(self.label)
        self.setLayout(layout)

        self.reloadUI()

    def reloadUI(self):
        self.font_size = int(self.settings.value("USER/FONT_SIZE"))
        self.font.setPointSize(self.font_size)
        self.label.setFont(self.font)
        self.label.setStyleSheet(
            f"color: {self.settings.value('USER/FONT_COLOR')}; "
            f"background-color: {self.settings.value('USER/BG_COLOR')}"
        )

    def resetUI(self):
        default_bg_color = self.settings.value("DEFAULT/BG_COLOR")
        default_font_color = self.settings.value("DEFAULT/FONT_COLOR")
        default_font_size = self.settings.value("DEFAULT/FONT_SIZE")

        self.settings.setValue("USER/BG_COLOR", default_bg_color)
        self.settings.setValue("USER/FONT_COLOR", default_font_color)
        self.settings.setValue("USER/FONT_SIZE", default_font_size)

        self.reloadUI()

    def increaseFontSize(self):
        self.font_size += self.font_size_step
        self.changeFontSize()

    def decreaseFontSize(self):
        self.font_size -= self.font_size_step
        self.changeFontSize()

    def changeFontSize(self):
        font = self.label.font()
        font.setPointSize(self.font_size)
        self.label.setFont(font)

    def setFontColor(self, color: str) -> None:
        self.settings.setValue("USER/FONT_COLOR", color)
        self.reloadUI()

    def setBackgroundColor(self, color: str) -> None:
        self.settings.setValue("USER/BG_COLOR", color)
        self.reloadUI()

    def mousePressEvent(self, event: QMouseEvent) -> None:
        self.pressed = True
        self.oldPos = event.pos()
        super().mousePressEvent(event)

    def mouseMoveEvent(self, event: QMouseEvent) -> None:
        if self.pressed:
            self.move(self.pos() + (event.pos() - self.oldPos))
        super().mouseMoveEvent(event)

    def mouseReleaseEvent(self, event: QMouseEvent) -> None:
        self.pressed = False
        self.oldPos = event.pos()
        super().mouseReleaseEvent(event)

    def mouseRightMenu(self, pos) -> None:
        menu = QMenu(self)

        # font size
        font_size_menu = menu.addMenu("font size")
        larger_action = QAction("larger", self)
        smaller_action = QAction("smaller", self)

        larger_action.triggered.connect(self.increaseFontSize)
        smaller_action.triggered.connect(self.decreaseFontSize)

        font_size_menu.addAction(larger_action)
        font_size_menu.addAction(smaller_action)

        ft_colors = ["none", "blue", "orange", "green", "red", "yellow", "white"]
        bg_colors = ["none", "blue", "orange", "green", "red", "yellow", "white"]

        # font color
        font_color_menu = menu.addMenu("font color")
        font_color_actions = [
            QAction(color, self, triggered=lambda c=color: self.setFontColor(c))
            for color in ft_colors
        ]
        font_color_menu.addActions(font_color_actions)

        # background color
        bg_color_menu = menu.addMenu("bg color")
        bg_color_actions = [
            QAction(color, self, triggered=lambda c=color: self.setBackgroundColor(c))
            for color in bg_colors
        ]
        bg_color_menu.addActions(bg_color_actions)

        # reset
        reset_action = QAction("reset", self)
        reset_action.triggered.connect(self.resetUI)
        menu.addAction(reset_action)

        # quit
        quit_action = QAction("quit", self)
        quit_action.triggered.connect(self.close)
        menu.addAction(quit_action)

        menu.exec(self.mapToGlobal(pos))

    def showTime(self):
        current_time = QTime.currentTime().toString("hh:mm")
        self.label.setText(current_time)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    clock = Clock()
    clock.show()  # show all the widgets
    app.exit(app.exec())  # start the app
