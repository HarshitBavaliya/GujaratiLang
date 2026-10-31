# GujaratiLang v2.6.0: Kasauti (કસોટી) E2E Browser & Frontend Testing Suite (વેબસાઇટ ફ્રન્ટએન્ડ કસોટી)

GujaratiLang **v2.6.0** is officially released! Named after the authentic Gujarati word for touchstone and gold standard examination, **Kasauti (કસોટી)** brings comprehensive end-to-end frontend browser automation and UI testing to GujaratiLang—inspired by the expressive syntax of Laravel Dusk.

With v2.1.0's **Laravel Eloquent ORM** and **Laravel Blade Templating**, GujaratiLang v2.6.0 completes the **full-stack Laravel triumvirate** in native Gujarati:
$$\text{Eloquent ORM (Data)} + \text{Blade Templates (Views)} + \text{Kasauti Testing (Browser E2E)}$$

This release also elevates the GujaratiLang automated test suite to the **515 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v2.6.0

### 1. 👁️ Kasauti (કસોટી) Fluent Browser Testing API
Expressive browser automation supporting both sub-millisecond in-engine Virtual DOM execution and real Headless Chrome/Edge WebDriver via the Chrome DevTools Protocol (CDP):
- **`kasauti_open([options])` / `કસોટી_ખોલો`**: Launches a virtual or real headless browser session with custom viewport (`1280x800`).
- **`kasauti_visit(b, url)` / `કસોટી_મુલાકાત`**: Navigates to any web route, full URL, or internal server endpoint.
- **`kasauti_type(b, selector, text)` / `કસોટી_લખો`**: Types text into inputs, textareas, and form fields.
- **`kasauti_press(b, button_text)` / `કસોટી_દબાવો`** & **`kasauti_click(b, selector)` / `કસોટી_ક્લિક`**: Triggers form submissions, button presses, and anchor navigations.
- **`kasauti_select(b, selector, value)` / `કસોટી_પસંદ`**: Interacts with dropdown menus and select controls.
- **`kasauti_screenshot(b, path)` / `કસોટી_સ્ક્રીનશોટ`**: Captures audit screenshots and page snapshots.
- **`kasauti_cookie(b, key, [value])` / `કસોટી_કૂકી`**: Manages session cookies and authentication state.
- **`kasauti_close(b)` / `કસોટી_બંધ`**: Safely releases browser resources.

### 2. 🛡️ Comprehensive Dusk-Style Browser Assertions
Ensure user interface elements and text are rendered accurately:
- **`kasauti_assert_see(b, text)` / `કસોટી_ખાતરી_જોવા_મળ્યું`**: Asserts that visible text exists on the page.
- **`kasauti_assert_dont_see(b, text)` / `કસોટી_ખાતરી_નથી_દેખાતું`**: Verifies error messages or unauthorized elements are absent.
- **`kasauti_assert_path(b, expected_path)` / `કસોટી_ખાતરી_પાથ`**: Asserts the current URL path matches expectations (e.g., redirect to `/dashboard`).
- **`kasauti_assert_title(b, expected_title)` / `કસોટી_ખાતરી_શીર્ષક`**: Asserts the document `<title>` tag matches.
- **`kasauti_assert_present(b, selector)` / `કસોટી_ખાતરી_હાજર`**: Checks DOM element presence by CSS ID or selector.

### 3. 🧰 Native CLI Subcommands
- **`gujarati kasauti [path]`**: Discovers and runs all `*.kasauti.gj` and `*_test.gj` files, producing colorized test summaries and reports.
- **`gujarati kasauti:make <TestName>`**: Generates starter scaffold test files in `tests/kasauti/`.
- **`gujarati kasauti:chrome`**: Diagnostic scanner verifying Chrome, Chromium, Edge, and port `9222` readiness.

---

## 🛡️ The 515 Tests Milestone (100% Pass Rate)
GujaratiLang v2.6.0 expands automated testing to **515 automated test suites**:
- **503 Language & Subsystem Test Suites**: Comprehensive coverage spanning core lexing, parsing, AST execution, Eloquent ORM, Blade templating, Redis-style caching, Pub/Sub, Desktop GUI, 2D Canvas, Android Camera/Sensors, AOT Compiler, C-FFI, and the new Kasauti browser testing engine.
- **12 Production Example Programs**: Fibonacci, Temperature Converter, Inventory, Stock, Calculator, String Utils, CSV Parser, Math Suite, Text Filter, Report Generator, Invoice Generator, and Random Game.
- **100% CTest Pass Rate** across Windows x64, Linux x64, macOS x64, and macOS ARM64.

---

## 🌐 Live Website & Playground
The official portal and interactive playground are updated to **v2.6.0**:
- **Official Website**: [https://gujaratilang.hp-square.com/](https://gujaratilang.hp-square.com/)
- **Version Archive**: [https://gujaratilang.hp-square.com/history.html](https://gujaratilang.hp-square.com/history.html)
- **New Playground Preset**:
  - 👁️ *Kasauti (કસોટી) Browser & E2E Testing*
