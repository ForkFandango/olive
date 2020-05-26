/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2019 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef RENDERTASK_H
#define RENDERTASK_H

#include <QtConcurrent/QtConcurrent>

#include "node/output/viewer/viewer.h"
#include "task/task.h"

OLIVE_NAMESPACE_ENTER

class RenderTask : public Task
{
public:
  RenderTask(ViewerOutput* viewer, const VideoRenderingParams &vparams, const AudioRenderingParams &aparams);

protected:
  void Render(const TimeRangeList &video_range,
              const TimeRangeList &audio_range,
              const QMatrix4x4 &mat,
              bool use_disk_cache);

  virtual QFuture<void> DownloadFrame(FramePtr frame, const QByteArray &hash) = 0;

  virtual void FrameDownloaded(const QByteArray& hash, const std::list<rational>& times) = 0;

  virtual void AudioDownloaded(const TimeRange& range, SampleBufferPtr samples) = 0;

  ViewerOutput* viewer() const
  {
    return viewer_;
  }

  VideoRenderingParams video_params() const
  {
    return video_params_;
  }

  AudioRenderingParams audio_params() const
  {
    return audio_params_;
  }

  void SetAnchorPoint(const rational& r);

private:
  ViewerOutput* viewer_;

  VideoRenderingParams video_params_;

  AudioRenderingParams audio_params_;

  rational anchor_point_;

};

OLIVE_NAMESPACE_EXIT

#endif // RENDERTASK_H
