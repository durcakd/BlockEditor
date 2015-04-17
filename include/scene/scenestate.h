#ifndef SCENESTATE_H
#define SCENESTATE_H


class AbstractElement;

class SceneState
{
public:
    SceneState();

    AbstractElement *getSelectedItem() const;
    AbstractElement *getPaintedElement() const;
    void setSelectedItem(AbstractElement *selectedItem);
    void setPaintedElement(AbstractElement *paintedElement);

private:
    AbstractElement *_selectedItem;
    AbstractElement *_paintedElement;

};

#endif // MAINWINDOW_H
