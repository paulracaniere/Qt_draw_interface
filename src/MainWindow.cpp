#include "MainWindow.h"

#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent) {

    // Creates a drawing zone in the window
    canvas = new Canvas(this);
    setCentralWidget(canvas);

    // Creates basic menus
    QMenuBar *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu(tr("File"));
    QMenu *editMenu = menuBar->addMenu(tr("Edit"));

    // Overrides standard Qt quitting action
    auto quit_action = new QAction(QIcon("icons/quit.png"), tr("Quit"), this);
    quit_action->setShortcut(QKeySequence("Ctrl+Q"));
    quit_action->setToolTip(tr("Quit program"));
    fileMenu->addAction(quit_action);
    quit_action->setIconVisibleInMenu(false);
    connect(quit_action, &QAction::triggered, this, &MainWindow::close);

    // Defines a cancel / undo action
    auto cancel_action = new QAction(QIcon("icons/cancel.png"), tr("Cancel"), this);
    cancel_action->setShortcut(QKeySequence("Ctrl+Z"));
    cancel_action->setToolTip(tr("Cancel last action"));
    cancel_action->setIconVisibleInMenu(false);
    editMenu->addAction(cancel_action);
    connect(cancel_action, &QAction::triggered, canvas, &Canvas::deleteLastShape);

    // Defines a open action
    auto open_action = new QAction(QIcon("icons/open.png"), tr("Open"), this);
    open_action->setShortcut(QKeySequence("Ctrl+O"));
    open_action->setToolTip(tr("Open"));
    open_action->setIconVisibleInMenu(false);
    editMenu->addAction(open_action);
    connect(open_action, &QAction::triggered, canvas, &Canvas::readAllShapes);

    // Defines a save action
    auto save_action = new QAction(QIcon("icons/save.png"), tr("Save"), this);
    save_action->setShortcut(QKeySequence("Ctrl+S"));
    save_action->setToolTip(tr("Saves all shapes"));
    save_action->setIconVisibleInMenu(false);
    editMenu->addAction(save_action);
    connect(save_action, &QAction::triggered, canvas, &Canvas::saveAllShapes);

    // Defines a erase all action
    auto delete_all_action = new QAction(QIcon("icons/delete_all.png"), tr("Delete all"), this);
    delete_all_action->setShortcut(QKeySequence("Ctrl+Shift+D"));
    delete_all_action->setToolTip(tr("Delete all lines"));
    delete_all_action->setIconVisibleInMenu(false);
    editMenu->addAction(delete_all_action);
    connect(delete_all_action, &QAction::triggered, canvas, &Canvas::deleteAllShapes);

    editMenu->addSeparator();

    // Defines a color menu for drawing
    auto color_action = new QAction(tr("Color"), this);
    color_action->setShortcut(QKeySequence("Ctrl+Alt+C"));
    color_action->setIcon(QIcon("icons/color.png"));
    color_action->setIconVisibleInMenu(false);
    editMenu->addAction(color_action);
    connect(color_action, &QAction::triggered, this, &MainWindow::openColorMenu);

    // Defines the brush / pen toolbar that is visible if the user commands it
    auto brushToolBar = new QToolBar(tr("Brush"), this);
    brushToolBar->setMovable(false);
    brushToolBar->setVisible(false);

    // Brush button
    auto brush_action = new QAction(tr("Brush"), this);
    brush_action->setCheckable(true);
    brush_action->setShortcut(QKeySequence("Ctrl+Alt+B"));
    brush_action->setIcon(QIcon("icons/brush.png"));
    brush_action->setIconVisibleInMenu(false);
    editMenu->addAction(brush_action);
    connect(brush_action, &QAction::triggered, brushToolBar, &QToolBar::setVisible);

    // Mouse mode actions
    auto mouseModActionGroup = new QActionGroup(this);
    mouseModActionGroup->setExclusive(true);
    mouseModActionGroup->addAction(QIcon("icons/select.png"), tr("Selection"));
    mouseModActionGroup->addAction(QIcon("icons/line.png"), tr("Line"));
    mouseModActionGroup->addAction(QIcon("icons/rectangle.png"), tr("Rectangle"));
    mouseModActionGroup->addAction(QIcon("icons/ellipse.png"), tr("Ellipse"));
    for (auto i = 0; i < mouseModActionGroup->actions().size(); i++) {
        QAction *action = mouseModActionGroup->actions()[i];
        action->setCheckable(true);
        action->setData(i);
    }
    mouseModActionGroup->actions()[0]->setChecked(true);
    connect(mouseModActionGroup, &QActionGroup::triggered, canvas, &Canvas::setMouseMod);

    brushToolBar->addSeparator();

    // Pen style actions
    auto penStyleActionGroup = new QActionGroup(this);
    penStyleActionGroup->setExclusive(true);
    penStyleActionGroup->addAction(QIcon("icons/solid.png"), tr("Solid line"));
    penStyleActionGroup->addAction(QIcon("icons/dashed.png"), tr("Dashed line"));
    penStyleActionGroup->addAction(QIcon("icons/dotted.png"), tr("Dotted Line"));
    penStyleActionGroup->addAction(QIcon("icons/dashed_dotted.png"), tr("Dashed Dotted Line"));
    penStyleActionGroup->addAction(QIcon("icons/dashed_dotted_dotted.png"), tr("Dashed Dotted Dotted Line"));
    for (auto i = 0; i < penStyleActionGroup->actions().size(); i++) {
        QAction *action = penStyleActionGroup->actions()[i];
        action->setCheckable(true);
        action->setData(i);
    }
    penStyleActionGroup->actions()[0]->setChecked(true);
    connect(penStyleActionGroup, &QActionGroup::triggered, canvas, &Canvas::setPenStyle);
    brushToolBar->addActions(penStyleActionGroup->actions());

    brushToolBar->addSeparator();

    // Pen cap style actions
    auto penCapStyleActionGroup = new QActionGroup(this);
    penCapStyleActionGroup->setExclusive(true);
    penCapStyleActionGroup->addAction(tr("Flat Cap"));
    penCapStyleActionGroup->addAction(tr("Square Cap"));
    penCapStyleActionGroup->addAction(tr("Round Cap"));
    penCapStyleActionGroup->addAction(tr("MPen Cap"));
    for (auto i = 0; i < penCapStyleActionGroup->actions().size(); i++) {
        QAction *action = penCapStyleActionGroup->actions()[i];
        action->setCheckable(true);
        action->setData(i);
    }
    penCapStyleActionGroup->actions()[0]->setChecked(true);
    connect(penCapStyleActionGroup, &QActionGroup::triggered, canvas, &Canvas::setPenCapStyle);
    brushToolBar->addActions(penCapStyleActionGroup->actions());

    brushToolBar->addSeparator();

    // Pen join style actions
    auto penJoinStyleActionGroup = new QActionGroup(this);
    penJoinStyleActionGroup->setExclusive(true);
    penJoinStyleActionGroup->addAction(tr("Miter Join"));
    penJoinStyleActionGroup->addAction(tr("Bevel Join"));
    penJoinStyleActionGroup->addAction(tr("Round Join"));
    penJoinStyleActionGroup->addAction(tr("SVG Miter Join"));
    penJoinStyleActionGroup->addAction(tr("MPen Join"));
    for (auto i = 0; i < penJoinStyleActionGroup->actions().size(); i++) {
        QAction *action = penJoinStyleActionGroup->actions()[i];
        action->setCheckable(true);
        action->setData(i);
    }
    penJoinStyleActionGroup->actions()[0]->setChecked(true);
    connect(penJoinStyleActionGroup, &QActionGroup::triggered, canvas, &Canvas::setPenJoinStyle);
    brushToolBar->addActions(penJoinStyleActionGroup->actions());

    brushToolBar->addSeparator();

    // Defines a action whether to fill the shape or not
    auto brushFillAction = new QAction(tr("Fill"), this);
    brushFillAction->setCheckable(true);
    brushToolBar->addAction(brushFillAction);
    connect(brushFillAction, &QAction::triggered, canvas, &Canvas::setBrushFill);

    brushToolBar->addSeparator();

    // Brush width action
    auto brushWidthSpinBox = new QSpinBox(this);
    brushWidthSpinBox->setSuffix("px");
    brushWidthSpinBox->setToolTip(tr("Pen width"));
    brushWidthSpinBox->setMinimum(1);
    brushWidthSpinBox->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    connect(brushWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), canvas, &Canvas::setLineWidth);
    brushToolBar->addWidget(brushWidthSpinBox);

    // Defines the edit tool bar that contains most of the actions not specific to the drawing
    auto editToolBar = new QToolBar(tr("Edit"), this);
    editToolBar->setMovable(false);
    editToolBar->addActions(mouseModActionGroup->actions());
    editToolBar->addSeparator();
    editToolBar->addAction(open_action);
    editToolBar->addAction(save_action);
    editToolBar->addAction(cancel_action);
    editToolBar->addAction(delete_all_action);
    editToolBar->addSeparator();
    editToolBar->addAction(color_action);
    editToolBar->addAction(brush_action);

    // Sets the positions of the tool bars in the window
    addToolBar(Qt::LeftToolBarArea, editToolBar);
    addToolBar(Qt::RightToolBarArea, brushToolBar);
}

void MainWindow::openColorMenu() {
    // Wraps Qt function to load the color from the color menu of the OS
    QColor color = QColorDialog::getColor(canvas->getColor(), this);
    if (color.isValid()) canvas->setColor(color);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // Redefines the closing event of the window to make sure the user want to quit
    if (QMessageBox::question(this, tr("Closing?"), tr("Are you sure you want to quit?")) ==
        QMessageBox::Yes)
        event->accept();
    else event->ignore();
}
