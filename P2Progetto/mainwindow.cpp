#include "mainwindow.h"
#include "controller.h"
#include <QRegularExpressionValidator>
#include <iostream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), enterName(new QLineEdit(parent)){}

void MainWindow::menuIn(QMenuBar* menu){
    file = new QMenu("File", menu);
    chart = new QMenu("Chart", menu);
    edit = new QMenu("Edit", menu);
    file->addAction(new QAction("Open..",file));
    file->addAction(new QAction("Save", file));
    file->addAction(new QAction("Save as", file));
    chart->addAction(new QAction("Line Chart", chart));
    chart->addAction(new QAction("Bar Chart", chart));
    chart->addAction(new QAction("Pie Chart", chart));
    edit->addAction(new QAction("Graph Name", edit));
    edit->addAction(new QAction("Update Chart", edit));
    edit->addAction(new QAction("Add Cell", edit));
    edit->addAction(new QAction("Remove Cell", edit));

    menu->addMenu(file);
    menu->addMenu(chart);
    menu->addMenu(edit);
}

void MainWindow::buttonIn(QHBoxLayout* layout){
    lineGraph = new QPushButton("Line Chart", this);
    barGraph = new QPushButton("Bar Chart", this);
    pieGraph = new QPushButton("Pie Chart", this);
    updateGraph = new QPushButton("Update Graph", this);
    addCell = new QPushButton("Add Cell", this);
    removeCell = new QPushButton("Remove Cell", this);

    layout->addWidget(lineGraph);
    layout->addWidget(barGraph);
    layout->addWidget(pieGraph);
    layout->addSpacing(20);
    layout->addWidget(updateGraph);
    layout->addWidget(addCell);
    layout->addWidget(removeCell);
}

void MainWindow::contentIn(QHBoxLayout* layout){
    QVBoxLayout* g = new QVBoxLayout;
    grid = new QTableWidget(this);
    grid->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    grid->resizeColumnsToContents();
    grid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    chartName = new QLabel(this);
    chartName->setAlignment(Qt::AlignHCenter);
    cont->initGrid();
    g->addWidget(chartName);
    g->addWidget(grid);

    chartPlot = new QChartView(this);
    cont->setUpChart();

    layout->addLayout(g);
    layout->addWidget(chartPlot);
}

void MainWindow::connectButtons(){
    connect(lineGraph, SIGNAL(clicked()), cont, SLOT(lineVM()));
    connect(barGraph, SIGNAL(clicked()), cont, SLOT(barVM()));
    connect(pieGraph, SIGNAL(clicked()), cont, SLOT(pieVM()));
    connect(updateGraph, SIGNAL(clicked()), cont, SLOT(updateGraphPlot()));
    connect(addCell, SIGNAL(clicked()), this, SLOT(addCellDialog()));
    connect(removeCell, SIGNAL(clicked()), this, SLOT(removeCellDialog()));
}

void MainWindow::addCellDialog(){
    QDialog* addC = new QDialog(this);
    QPushButton* okAdd = new QPushButton("Add Cell");
    QPushButton* cancelAdd = new QPushButton("Cancel");
    numberAdd = new QSpinBox(this);

    QVBoxLayout* main = new QVBoxLayout;
    QHBoxLayout* buttons = new QHBoxLayout;

    buttons->addWidget(okAdd);
    buttons->addWidget(cancelAdd);
    main->addWidget(numberAdd);
    main->addLayout(buttons);

    numberAdd->setMinimum(1);
    numberAdd->setMaximum(cont->getElemNumber() + 1);


    connect(okAdd, SIGNAL(clicked()), cont, SLOT(addCell()));
    connect(okAdd, SIGNAL(clicked()), addC, SLOT(accept()));
    connect(cancelAdd, SIGNAL(clicked()), addC, SLOT(accept()));

    addC->setLayout(main);
    addC->setFixedSize(200, 100);
    addC->setWindowTitle("Add Cell");
    addC->exec();
}

void MainWindow::removeCellDialog(){
    QDialog* removeC = new QDialog;
    QPushButton* okRem = new QPushButton("Remove Cell");
    QPushButton* cancelRem = new QPushButton("Cancel");
    numberRem = new QSpinBox(nullptr);

    QVBoxLayout* main = new QVBoxLayout;
    QHBoxLayout* buttons = new QHBoxLayout;

    buttons->addWidget(okRem);
    buttons->addWidget(cancelRem);
    main->addWidget(numberRem);
    main->addLayout(buttons);

    numberRem->setMinimum(1);
    numberRem->setMaximum(cont->getElemNumber());

    connect(okRem, SIGNAL(clicked()), cont, SLOT(remCell()));
    connect(okRem, SIGNAL(clicked()), removeC, SLOT(accept()));
    connect(cancelRem, SIGNAL(clicked()), removeC, SLOT(accept()));

    removeC->setLayout(main);
    removeC->setFixedSize(200, 100);
    removeC->setWindowTitle("Remove Cell");
    removeC->exec();
}

void MainWindow::setNameDialog(){
    QDialog* setName = new QDialog;
    QPushButton* okSet = new QPushButton("Change Name");
    QPushButton* cancelSet = new QPushButton("Cancel");
    enterName->clear();
    enterName->setPlaceholderText("Enter Name");

    QVBoxLayout* main = new QVBoxLayout;
    QHBoxLayout* buttons = new QHBoxLayout;

    buttons->addWidget(okSet);
    buttons->addWidget(cancelSet);
    main->addWidget(enterName);
    main->addLayout(buttons);

    connect(okSet, SIGNAL(clicked()), cont, SLOT(setName()));
    connect(okSet, SIGNAL(clicked()), setName, SLOT(accept()));
    connect(cancelSet, SIGNAL(clicked()), setName, SLOT(accept()));

    setName->setLayout(main);
    setName->setFixedSize(200, 100);
    setName->setWindowTitle("Set Name");
    setName->exec();
}

void MainWindow::openFile(){
    QFileDialog* dialog = new QFileDialog(this, tr("Open File"));
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setNameFilter(tr("Json File (*.json)"));
    connect(dialog, SIGNAL(fileSelected(QString)), cont, SLOT(setPath(QString)));

    dialog->exec();
}

void MainWindow::saveAs(){
    QFileDialog* dialog = new QFileDialog(this, tr("Save As"), "untitled");
    dialog->setFileMode(QFileDialog::AnyFile);
	dialog->setAcceptMode(QFileDialog::AcceptSave);
    dialog->setNameFilter(tr("Json File (*.json)"));
    connect(dialog, SIGNAL(fileSelected(QString)), cont, SLOT(setPathNew(QString)));
    connect(dialog, SIGNAL(fileSelected(QString)), cont, SLOT(createJsonFile()));
    dialog->exec();
}

void MainWindow::errorDialog(){
    QDialog* d = new QDialog(nullptr);
    QVBoxLayout* v = new QVBoxLayout;
    QLabel* msg = new QLabel("Data entered not a number or fraction. Be sure to use the period instead of the comma and remove any space.");
    QPushButton * button = new QPushButton("Ok");
    QAbstractButton::connect(button, SIGNAL(clicked()), d, SLOT(accept()));
    v->addWidget(msg);
    v->addWidget(button);
    d->setLayout(v);
    d->setFixedSize(700, 80);
    d->setWindowTitle("Try again");
    d->exec();
}

MainWindow::~MainWindow(){}

void MainWindow::connectMenu(){
    connect(grid, SIGNAL(cellChanged(int,int)), cont, SLOT(updateModel(int,int)));
    connect(file->actions().at(0), SIGNAL(triggered()), this, SLOT(openFile()));
    connect(file->actions().at(1), SIGNAL(triggered()), cont, SLOT(checkPath()));
    connect(file->actions().at(2), SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(chart->actions().at(0), SIGNAL(triggered()), cont, SLOT(lineVM()));
    connect(chart->actions().at(1), SIGNAL(triggered()), cont, SLOT(barVM()));
    connect(chart->actions().at(2), SIGNAL(triggered()), cont, SLOT(pieVM()));
    connect(edit->actions().at(0), SIGNAL(triggered()), this, SLOT(setNameDialog()));
    connect(edit->actions().at(1), SIGNAL(triggered()), cont, SLOT(updateGraphPlot()));
    connect(edit->actions().at(2), SIGNAL(triggered()), this, SLOT(addCellDialog()));
    connect(edit->actions().at(3), SIGNAL(triggered()), this, SLOT(removeCellDialog()));
    connectButtons();
}

void MainWindow::init(controller *c){
    cont = c;
    QWidget* central = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QMenuBar* menu = new QMenuBar(this);
    menuIn(menu);
    QHBoxLayout* buttonLine = new QHBoxLayout;
    buttonIn(buttonLine);
    QHBoxLayout* content = new QHBoxLayout;
    contentIn(content);

    setMenuBar(menu);
    mainLayout->addLayout(buttonLine);
    mainLayout->addLayout(content);
    central->setLayout(mainLayout);
    setCentralWidget(central);
    setWindowTitle("Progetto PAO");
}

void MainWindow::setGridColumn(int i){
    grid->setColumnCount(i);
}

int MainWindow::getGridColumn() const{
    return grid->columnCount();
}



void MainWindow::addEleGrid(){
    if(grid->rowCount()){
        grid->setRowCount(grid->rowCount()+1);
    } else {
        grid->setRowCount(1);
    }
}

void MainWindow::insertEleGrid(int x){
    if(x > grid->rowCount()){
        grid->setRowCount(x);
    } else {
        grid->insertRow(x - 1);
    }
    grid->setItem(x - 1, 0, new QTableWidgetItem("Default"));
    int i = grid->columnCount();
    for(int j = 1; j < i; ++j){
        setCellData(0, x - 1, j);
    }
}

void MainWindow::removeEleGrid(int x){
    grid->removeRow(x);
}

void MainWindow::setGridHeaders(QStringList *s){
    grid->setHorizontalHeaderLabels(*s);
}

void MainWindow::setCellData(qreal v, int x, int y){
    grid->setItem(x,y,new QTableWidgetItem(QString::number(v)));
}

void MainWindow::setCellName(QString s, int x, int y){
    grid->setItem(x, y, new QTableWidgetItem(s));
}

QString MainWindow::getCellInput(int x, int y) const{
    return grid->item(x, y)->data(0).toString();
}

qreal MainWindow::getCellData(int x, int y) const{
    return grid->item(x, y)->data(0).toDouble();
}

QString MainWindow::getCellName(int x) const{
    return grid->item(x, 0)->text();
}

void MainWindow::setChartName(const QString &s){
    chartName->setText(s);
}

void MainWindow::updateChart(QChart* v){
    QChart * aux = chartPlot->chart();
    chartPlot->setChart(v);
    chartPlot->setRenderHint(QPainter::Antialiasing);
    delete aux;
}

int MainWindow::getCellNum(){
    return numberAdd->value();
}

int MainWindow::getCellRemNum(){
    return numberRem->value();
}

QString MainWindow::getNameEnter(){
    return enterName->text();
}

void MainWindow::cleanGrid(){
    disconnect(grid, SIGNAL(cellChanged(int,int)), cont, SLOT(updateModel(int,int)));
    grid->clear();
    grid->setColumnCount(0);
    grid->setRowCount(0);
    connect(grid, SIGNAL(cellChanged(int,int)), cont, SLOT(updateModel(int,int)));
}

bool MainWindow::changed() const{
    return changedGrid;
}

void MainWindow::hasChanged(bool b){
    changedGrid = b;
}







