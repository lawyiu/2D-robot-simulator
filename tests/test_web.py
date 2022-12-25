import unittest
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from robotsim import RobotSim


class RobotSimTests(unittest.TestCase):
    WAIT_TIMEOUT = 10
    URL = 'https://lawyiu.github.io/2D-robot-simulator/'
    COMPILING_MESSAGE = 'Compiling'
    COMPILER_SUCCESS_MESSAGE = 'Successfully compiled'
    COMPILER_ERROR_MESSAGE = 'Compilation Error'
    RESTARTING_SIMULATION_MESSAGE = "Restarting simulation..."

    HELLO_WORLD_PROG = 'void setup() {\nSerial.begin(9600);\nSerial.println("hello world");'
    INVALID_PROG = 'void setup() {\nSerial.begin(9600);\nSerial.println("hello world")'

    def test_compile_hello_world_program_should_succeed(self):
        sim = RobotSim(self.driver, self.URL)

        prev_compiler_msgs = sim.get_compiler_console_text()

        sim.compile_program(self.HELLO_WORLD_PROG)

        compiler_msgs = self.wait_for_text_condition(
            sim.get_compiler_console_text, self.cond_not_eq, prev_compiler_msgs)

        except_msg = 'Expected compiler messages to contain "{0}" but it did not. Compiler console output: "{1}"'
        self.assertTrue(self.COMPILING_MESSAGE in compiler_msgs,
                        except_msg.format(self.COMPILING_MESSAGE, compiler_msgs))

        compiler_msgs = self.wait_for_text_condition(
            sim.get_compiler_console_text, self.cond_contains, self.COMPILER_SUCCESS_MESSAGE)

        except_msg = 'Expected compiler messages to contain "{0}" but it did not. Compiler console output: "{1}"'
        self.assertTrue(self.COMPILER_SUCCESS_MESSAGE in compiler_msgs, except_msg.format(
            self.COMPILER_SUCCESS_MESSAGE, compiler_msgs))

    def test_compile_invalid_program_should_error(self):
        sim = RobotSim(self.driver, self.URL)

        prev_compiler_msgs = sim.get_compiler_console_text()

        sim.compile_program(self.INVALID_PROG)

        compiler_msgs = self.wait_for_text_condition(
            sim.get_compiler_console_text, self.cond_not_eq, prev_compiler_msgs)

        except_msg = 'Expected compiler messages to contain "{0}" but it did not. Compiler console output: "{1}"'
        self.assertTrue(self.COMPILING_MESSAGE in compiler_msgs,
                        except_msg.format(self.COMPILING_MESSAGE, compiler_msgs))

        compiler_msgs = self.wait_for_text_condition(
            sim.get_compiler_console_text, self.cond_contains, self.COMPILER_ERROR_MESSAGE)

        except_msg = 'Expected compiler messages to contain "{0}" but it did not. Compiler console output: "{1}"'
        self.assertTrue(self.COMPILER_ERROR_MESSAGE in compiler_msgs, except_msg.format(
            self.COMPILER_ERROR_MESSAGE, compiler_msgs))

    def test_switch_programs_should_change_program(self):
        sim = RobotSim(self.driver, self.URL)

        prev_prog_text = sim.get_program_editor_text()

        sim.change_program_select_index(1)

        new_prog_text = self.wait_for_text_condition(
            sim.get_program_editor_text, self.cond_not_eq, prev_prog_text)

        self.assertNotEqual(prev_prog_text, new_prog_text,
                            'Previous editor text is same as current editor text: %s' % new_prog_text)

    def test_uncheck_restart_sim_after_compiling(self):
        sim = RobotSim(self.driver, self.URL)

        self.assertTrue(sim.is_restart_checkbox_checked(), "Restart simulation checkbox is not checked by default")

        sim.click_restart_checkbox()
        self.assertFalse(sim.is_restart_checkbox_checked(),
            "Restart simulation checkbox is checked even after unchecking it by clicking it")

        sim.click_compile_program_button()

        prev_compiler_msg = sim.get_compiler_console_text()
        new_compiler_msg = self.wait_for_text_condition(sim.get_compiler_console_text, self.cond_not_eq, prev_compiler_msg)

        self.assertFalse(self.RESTARTING_SIMULATION_MESSAGE in new_compiler_msg,
            "%s in compiler output even with restart simulation checkbox unchecked" % self.RESTARTING_SIMULATION_MESSAGE)

    def test_check_restart_sim_after_unchecking(self):
        sim = RobotSim(self.driver, self.URL)

        self.assertTrue(sim.is_restart_checkbox_checked(), "Restart simulation checkbox is not checked by default")

        sim.click_restart_checkbox()
        self.assertFalse(sim.is_restart_checkbox_checked(),
            "Restart simulation checkbox is checked even after unchecking it by clicking it")

        sim.click_restart_checkbox()
        self.assertTrue(sim.is_restart_checkbox_checked, "Restart simulation checkbox is unchecked after checking it again")

        sim.click_compile_program_button()

        prev_compiler_msg = sim.get_compiler_console_text()
        new_compiler_msg = self.wait_for_text_condition(sim.get_compiler_console_text, self.cond_not_eq, prev_compiler_msg)

        self.assertTrue(self.RESTARTING_SIMULATION_MESSAGE in new_compiler_msg,
            "%s not in compiler output even with restart simulation checkbox checked" % self.RESTARTING_SIMULATION_MESSAGE)

    @classmethod
    def wait_for_text_condition(cls, get_text_func, cond, text):
        new_text = None

        def text_fulfills_cond(_):
            nonlocal new_text
            new_text = get_text_func()
            return cond(new_text, text)

        WebDriverWait(cls.driver, cls.WAIT_TIMEOUT) \
            .until(text_fulfills_cond)

        return new_text

    @classmethod
    def cond_not_eq(cls, new_text, prev_text): return new_text != prev_text

    @classmethod
    def cond_contains(cls, new_text, text): return text in new_text

    @classmethod
    def setUpClass(cls):
        options = webdriver.ChromeOptions()
        options.add_argument('--log-level=3')
        cls.driver = webdriver.Chrome(options=options)
        cls.driver.maximize_window()

    @classmethod
    def tearDownClass(cls):
        cls.driver.quit()


if __name__ == '__main__':
    unittest.main()
