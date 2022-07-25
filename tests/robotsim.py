from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support.select import Select
from selenium.common.exceptions import ElementNotVisibleException


class RobotSim:
    SIM_TIMEOUT = 30
    PAGE_TITLE = '2D Robot Simulator'

    SPINNER_ID = 'spinner'
    PROGRAM_EDITOR_SEL = '#program-editor > .ace_text-input'
    COMPILE_BUTTON_SEL = '.editor-form button'
    COMPILER_CONSOLE_ID = 'compiler-console'
    SELECT_PROGRAM_ID = 'examples-selection'

    def __init__(self, driver, url):
        self.driver = driver
        self.url = url

        driver.get(url)

        actual_page_title = driver.title
        if actual_page_title != self.PAGE_TITLE:
            raise RuntimeError('On wrong page? Got page title: "%s" but expected "%s' % (
                actual_page_title, self.PAGE_TITLE))

        WebDriverWait(self.driver, self.SIM_TIMEOUT, ignored_exceptions=ElementNotVisibleException) \
            .until_not(lambda d: d.find_element(By.ID, self.SPINNER_ID).is_displayed())

        self.prog_edit_elm = self.driver.find_element(
            By.CSS_SELECTOR, self.PROGRAM_EDITOR_SEL)
        self.compile_btn_elm = self.driver.find_element(
            By.CSS_SELECTOR, self.COMPILE_BUTTON_SEL)
        self.compiler_console_elm = self.driver.find_element(
            By.ID, self.COMPILER_CONSOLE_ID)
        self.select_program_elm = self.driver.find_element(
            By.ID, self.SELECT_PROGRAM_ID)
        self.select_program = Select(self.select_program_elm)

    def get_program_editor_text(self):
        return self.prog_edit_elm.get_attribute('value')

    def clear_program_editor(self):
        # clear() does not work on the program editor, so using a workaround instead
        self.prog_edit_elm.send_keys(Keys.CONTROL, 'a')
        self.prog_edit_elm.send_keys(Keys.BACK_SPACE)

    def change_program_select_index(self, index):
        self.select_program.select_by_index(index)

    def compile_program(self, program):
        self.clear_program_editor()
        self.prog_edit_elm.send_keys(program)

        self.compile_btn_elm.click()

    def get_compiler_console_text(self):
        return self.compiler_console_elm.text
