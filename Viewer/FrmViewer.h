// Author: Kang Lin <kl222@126.com>

#ifndef FRMVIEWER_H
#define FRMVIEWER_H

#pragma once

#include <QWidget>
#include <QSettings>
#include "viewer_export.h"

class CConnecter;

namespace Ui {
class CFrmViewer;
}

/**
 * \~chinese
 * \brief 
 * 用于显示从 CConnect 输出的图像，和向 CConnect 发送键盘、鼠标事件。
 * 当新的输出图像从 CConnect 输出时，它调用 slotUpdateRect() 更新显示。
 *
 * \~english
 * \brief 
 * A widget which displays output image from a CConnect
 * and sends input keypresses and mouse activity
 * to the CConnect.
 *
 * When the viewer receives new output from the CConnect,
 * it will update the display by calling slotUpdateRect().
 * 
 *\~
 * \see  CConnecter CConnect
 * \ingroup VIEWER_PLUGIN_API
 */
class VIEWER_EXPORT CFrmViewer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double ZoomFactor READ GetZoomFactor WRITE SetZoomFactor)

public:
    explicit CFrmViewer(QWidget *parent = nullptr);
    virtual ~CFrmViewer() override;
    
    /**
     * \~chinese 窗口适配枚举常量
     * \~english The ADAPT_WINDOWS enum
     */
    enum ADAPT_WINDOWS {
        Disable = 0,                  ///< \~english Disable adapt windows
                                      ///< \~chinese 禁用适配窗口
        Auto = 1,
        Original = 2,                 ///< \~english Original desktop size, the left-top of the desktop is aligned with the left-top of the window
                                      ///< \~chinese 原始桌面大小，桌面的左上点与窗口的左上点对齐
        OriginalCenter = 3,           ///< \~english Original desktop size, the center of the desktop is aligned with the center of the window
                                      ///< \~chinese 原始桌面大小，桌面中心点与窗口中心点对齐
        Zoom = 4,                     ///< \~english zoom windows = destop size * factor
                                      ///< \~chinese 缩放窗口大小等于桌面大小 * 系数
        ZoomToWindow = 5,             ///< \~english Desktop adapt to windows
                                      ///< \~chinese 桌面缩放到窗口大小，窗口是固定的
        KeepAspectRationToWindow = 6, ///< \~english Keep desktop aspectration adapt to windows
                                      ///< \~chinese 保持长宽比缩放到窗口大小,窗口是固定的
    };
    void SetAdaptWindows(ADAPT_WINDOWS aw = Original);
    ADAPT_WINDOWS GetAdaptWindows();
    
    /*!
     * \~chinese 调整缩放系数。
     *  调整完成后需要调用 SetAdaptWindows(FrmViewer::Zoom) 缩放窗口大小。
     * \~english Adjust the zoom factor. After the adjustment is completed,
     *  you need to call SetAdaptWindows(FrmViewer::Zoom) to zoom the window size. 
     * \return 
     */
    double GetZoomFactor() const;
    int SetZoomFactor(double newZoomFactor);
    QSize GetDesktopSize();

    virtual int Load(QSettings &set);
    virtual int Save(QSettings &set);

    virtual QImage GrabImage(int x = 0, int y = 0, int w = -1, int h = -1);

public Q_SLOTS:
    void slotSetDesktopSize(int width, int height);
    void slotSetName(const QString& szName);
    void slotUpdateRect(const QRect& r, const QImage& image);
    void slotUpdateCursor(const QCursor& cursor);
    void slotUpdateCursorPosition(const QPoint& pos);
    void slotSystemCombination();
    
Q_SIGNALS:
    void sigMousePressEvent(Qt::MouseButtons, QPoint);
    void sigMouseReleaseEvent(Qt::MouseButton, QPoint);
    void sigMouseMoveEvent(Qt::MouseButtons buttons, QPoint pos);
    void sigMouseMoveEvent(QMouseEvent *event);
    void sigWheelEvent(Qt::MouseButtons buttons, QPoint pos, QPoint angleDelta);
    void sigKeyPressEvent(int key, Qt::KeyboardModifiers modify);
    void sigKeyReleaseEvent(int key, Qt::KeyboardModifiers modify);
    
    // Please use CConnecter::sigServerName
    void sigServerName(const QString &szName);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

private:
    Ui::CFrmViewer *ui;
    QImage m_Desktop;

    ADAPT_WINDOWS m_AdaptWindows;
    double m_dbZoomFactor;
    
    int ReSize(int width, int height);
    void paintDesktop();
    int TranslationMousePoint(QPointF inPos, QPointF &outPos);
    QRectF GetAspectRationRect();
};

#endif // FRMVIEWER_H
