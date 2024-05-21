// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_PASSWORD_GENERATION_BUBBLE_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_PASSWORD_GENERATION_BUBBLE_VIEW_H_

#include "base/basictypes.h"
#include "ui/gfx/rect.h"
#include "ui/views/bubble/bubble_delegate.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/view.h"
#include "webkit/forms/password_form.h"

namespace autofill {
class PasswordGenerator;
}

namespace content {
class PageNavigator;
class RenderViewHost;
}

namespace views {
class ImageButton;
class Label;
class TextButton;
class Textfield;
}

class PasswordManager;

// PasswordGenerationBubbleView is a bubble used to show possible generated
// passwords to users. It is set in the page content, anchored at |anchor_rect|.
// If the generated password is accepted by the user, the renderer associated
// with |render_view_host| and the |password_manager| are informed.
class PasswordGenerationBubbleView : public views::BubbleDelegateView,
                                     public views::ButtonListener {
 public:
  PasswordGenerationBubbleView(const webkit::forms::PasswordForm& form,
                               const gfx::Rect& anchor_rect,
                               views::View* anchor_view,
                               content::RenderViewHost* render_view_host,
                               PasswordManager* password_manager,
                               autofill::PasswordGenerator* password_generator,
                               content::PageNavigator* navigator,
                               ui::ThemeProvider* theme_provider);
  virtual ~PasswordGenerationBubbleView();

  // views::View
  virtual gfx::Size GetPreferredSize() OVERRIDE;
  virtual void Layout() OVERRIDE;

 private:
  // views::BubbleDelegateView
  virtual void Init() OVERRIDE;
  virtual gfx::Rect GetAnchorRect() OVERRIDE;

  // views::ButtonListener
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  // views::WidgetDelegate
  virtual views::View* GetInitiallyFocusedView() OVERRIDE;

  // Subviews
  views::Label* title_label_;
  views::TextButton* accept_button_;
  views::Textfield* textfield_;
  views::ImageButton* regenerate_button_;
  views::View* textfield_wrapper_;

  // The form associated with the password field(s) that we are generated.
  webkit::forms::PasswordForm form_;

  // Location that the bubble points to
  gfx::Rect anchor_rect_;

  // RenderViewHost associated with the button that spawned this bubble.
  content::RenderViewHost* render_view_host_;

  // PasswordManager associated with this tab.
  PasswordManager* password_manager_;

  // Object to generate passwords. The class won't take the ownership of it.
  autofill::PasswordGenerator* password_generator_;

  // An object used to handle page loads that originate from link clicks
  // within this UI.
  content::PageNavigator* navigator_;

  // Theme provider used to draw the regenerate button.
  ui::ThemeProvider* theme_provider_;

  DISALLOW_COPY_AND_ASSIGN(PasswordGenerationBubbleView);
};

#endif  // CHROME_BROWSER_UI_VIEWS_PASSWORD_GENERATION_BUBBLE_VIEW_H_