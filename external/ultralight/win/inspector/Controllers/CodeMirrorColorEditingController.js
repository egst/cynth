/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

WI.CodeMirrorColorEditingController = class CodeMirrorColorEditingController extends WI.CodeMirrorEditingController
{
    // Public

    get initialValue()
    {
        return WI.Color.fromString(this.text);
    }

    get cssClassName()
    {
        return "color";
    }

    popoverWillPresent(popover)
    {
        this._colorPicker = new WI.ColorPicker;
        this._colorPicker.addEventListener(WI.ColorPicker.Event.ColorChanged, this._colorPickerColorChanged, this);
        this._colorPicker.addEventListener(WI.ColorPicker.Event.FormatChanged, (event) => popover.update());
        popover.content = this._colorPicker.element;
    }

    popoverDidPresent(popover)
    {
        this._colorPicker.color = this._value;
    }

    // Private

    _colorPickerColorChanged(event)
    {
        this.value = event.target.color;
    }
};
